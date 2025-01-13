# main.py
from mpi4py import MPI
from dsm_lib import DSM
import time

def value_changed(var_name: str, new_value: int):
    """Callback function for variable changes"""
    rank = MPI.COMM_WORLD.Get_rank()
    print(f"Process {rank}: Variable {var_name} changed to {new_value}")

# Run using:
# mpirun -n 4 python .
def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    # Initialize DSM
    dsm = DSM(rank, size)
    
    # Create variables with different subscriber groups
    if rank == 0:
        # Variable 'A' is shared between processes 0, 1, 2
        dsm.create_variable('A', 0, {0, 1, 2})
        # Variable 'B' is shared between processes 0, 2, 3
        dsm.create_variable('B', 0, {0, 2, 3})
        
        # Wait for other processes to initialize
        time.sleep(1)
        
        # Test write operations
        print(f"Process {rank}: Writing 42 to A")
        dsm.write('A', 42)
        
        time.sleep(1)
        print(f"Process {rank}: Writing 100 to B")
        dsm.write('B', 100)
        
        time.sleep(1)

        # Test compare and exchange
        print(f"Process {rank}: Attempting CAS on A (42 -> 43) should be True.")
        result = dsm.compare_and_exchange('A', 42, 43)
        print(f"Process {rank}: CAS result: {result}")

        time.sleep(1)

        print(f"Process {rank}: Attempting CAS on A (42 -> 69) should be False.")
        result = dsm.compare_and_exchange('A', 42, 69)
        print(f"Process {rank}: CAS result: {result}")
        
    else:
        # Other processes create the same variables
        if rank in {1, 2}:
            dsm.create_variable('A', 0, {0, 1, 2})
        if rank in {2, 3}:
            dsm.create_variable('B', 0, {0, 2, 3})
    
    # Subscribe to callbacks
    if rank in {0, 1, 2}:
        dsm.subscribe_callback('A', value_changed)
    if rank in {0, 2, 3}:
        dsm.subscribe_callback('B', value_changed)
    
    # Run for a while to process messages
    time.sleep(5)
    
    # Cleanup
    dsm.shutdown()

if __name__ == "__main__":
    main()