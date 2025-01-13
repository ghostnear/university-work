# dsm_lib.py
from mpi4py import MPI
from collections import defaultdict
from dataclasses import dataclass
from typing import Dict, Set, Callable, List
import threading
import queue
import time

@dataclass
class Variable:
    """Represents a DSM variable"""
    value: int
    subscribers: Set[int]
    version: int = 0

class DSM:
    def __init__(self, rank: int, size: int):
        """Initialize DSM with process rank and total size"""
        self.comm = MPI.COMM_WORLD
        self.rank = rank
        self.size = size
        self.variables: Dict[str, Variable] = {}
        self.callbacks: Dict[str, List[Callable]] = defaultdict(list)
        self.message_queue = queue.PriorityQueue()  # (version, var_name, value)
        self.next_version = 0
        self.subscriber_maps: Dict[str, Set[int]] = {}
        self.cas_results: Dict[int, bool] = {}  # Store CAS results by version
        self.cas_event = threading.Event()  # Event for CAS synchronization
        
        # Start message processing thread
        self.running = True
        self.process_thread = threading.Thread(target=self._process_messages)
        self.process_thread.start()

    def create_variable(self, var_name: str, initial_value: int, subscribers: Set[int]):
        """Create a new DSM variable"""
        if var_name in self.variables:
            raise ValueError(f"Variable {var_name} already exists")
        
        self.variables[var_name] = Variable(initial_value, subscribers)
        self.subscriber_maps[var_name] = subscribers

    def subscribe_callback(self, var_name: str, callback: Callable[[str, int], None]):
        """Subscribe to changes on a variable"""
        if var_name not in self.variables:
            raise ValueError(f"Variable {var_name} does not exist")
        if self.rank not in self.variables[var_name].subscribers:
            raise ValueError(f"Process {self.rank} is not subscribed to {var_name}")
        
        self.callbacks[var_name].append(callback)

    def write(self, var_name: str, value: int):
        """Write a value to a variable and notify subscribers"""
        if var_name not in self.variables:
            raise ValueError(f"Variable {var_name} does not exist")
        if self.rank not in self.variables[var_name].subscribers:
            raise ValueError(f"Process {self.rank} is not authorized to write to {var_name}")

        version = self._get_next_version()
        
        # Prepare update message
        message = {
            'type': 'write',
            'var_name': var_name,
            'value': value,
            'version': version,
            'sender': self.rank
        }
        
        # Send to all subscribers (including self)
        for subscriber in self.variables[var_name].subscribers:
            if subscriber != self.rank:
                self.comm.send(message, dest=subscriber)
        
        # Process own message
        self._handle_write(message)

    def compare_and_exchange(self, var_name: str, compare_value: int, new_value: int) -> bool:
        """Atomic compare and exchange operation"""
        if var_name not in self.variables:
            raise ValueError(f"Variable {var_name} does not exist")
        if self.rank not in self.variables[var_name].subscribers:
            raise ValueError(f"Process {self.rank} is not authorized to access {var_name}")

        version = self._get_next_version()
        
        # Initialize result storage for this version
        self.cas_results[version] = None
        
        # Prepare CAS message
        message = {
            'type': 'cas',
            'var_name': var_name,
            'compare_value': compare_value,
            'new_value': new_value,
            'version': version,
            'sender': self.rank
        }
        
        # Send to all subscribers
        for subscriber in self.variables[var_name].subscribers:
            if subscriber != self.rank:
                self.comm.send(message, dest=subscriber)
        
        # Process own message immediately
        self._handle_cas(message)
        
        # Wait for result with timeout
        start_time = time.time()
        while self.cas_results[version] is None:
            if time.time() - start_time > 5.0:  # 5 second timeout
                print(f"Process {self.rank}: CAS operation timed out")
                return False
            time.sleep(0.001)
        
        result = self.cas_results[version]
        del self.cas_results[version]  # Cleanup
        return result

    def _get_next_version(self) -> int:
        """Get next global version number"""
        version = self.next_version
        self.next_version += 1
        return version

    def _handle_write(self, message: dict):
        """Handle write message"""
        var_name = message['var_name']
        value = message['value']
        version = message['version']
        
        # Queue message for ordered processing
        self.message_queue.put((version, ('write', var_name, value)))

    def _handle_cas(self, message: dict):
        """Handle compare and exchange message"""
        var_name = message['var_name']
        compare_value = message['compare_value']
        new_value = message['new_value']
        version = message['version']
        
        # Queue message for ordered processing
        self.message_queue.put((version, ('cas', var_name, compare_value, new_value)))

    def _process_messages(self):
        """Process messages in version order"""
        while self.running:
            try:
                # Check for incoming messages
                while self.comm.Iprobe(source=MPI.ANY_SOURCE):
                    message = self.comm.recv(source=MPI.ANY_SOURCE)
                    if message['type'] == 'write':
                        self._handle_write(message)
                    elif message['type'] == 'cas':
                        self._handle_cas(message)

                # Process next message in queue
                if not self.message_queue.empty():
                    version, message = self.message_queue.get()
                    
                    if message[0] == 'write':
                        _, var_name, value = message
                        var = self.variables[var_name]
                        var.value = value
                        var.version = version
                        
                        # Notify callbacks
                        for callback in self.callbacks[var_name]:
                            callback(var_name, value)
                            
                    elif message[0] == 'cas':
                        _, var_name, compare_value, new_value = message
                        var = self.variables[var_name]
                        success = False
                        
                        if var.value == compare_value:
                            var.value = new_value
                            var.version = version
                            success = True
                            
                            # Notify callbacks
                            for callback in self.callbacks[var_name]:
                                callback(var_name, new_value)
                        
                        # Store the result
                        self.cas_results[version] = success
                
                time.sleep(0.001)  # Prevent busy waiting
                
            except Exception as e:
                print(f"Error in message processing: {e}")

    def shutdown(self):
        """Shutdown DSM system"""
        self.running = False
        self.process_thread.join()