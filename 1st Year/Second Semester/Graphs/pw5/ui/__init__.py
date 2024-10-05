from domain import *

class UI:
    _running : bool
    _runningOperations : bool
    _currentGraph : Graph

    def __init__(self):
        self._running = True
        self._runningOperations = False
        self._currentGraph = Graph(0)

    def _read_integer(self, message : str) -> int:
        result = []
        while result == []:
            try:
                result = int(input(message))
            except:
                result = []
                print("The input was not an integer.")
        return result

    def _read_string(self, message : str) -> str:
        return input(message)

    def _print_menu(self):
        print("\nGraph Operations Simulator\n")
        print("1. Read graph from a file.")
        print("2. Find a Hamiltonian cycle (if it exists).")
        print("3. Exit\n")

    def start(self):
        while self._running:
            self._print_menu()
            result = self._read_integer("Action > ")
            match result:
                case 1:
                    path = self._read_string("Path: ")
                    self._currentGraph = read_graph_from_file(path)

                case 2:
                    if not self._currentGraph.is_vertex(0):
                        print("\nGraph is empty!")
                    else:
                        result = self._currentGraph._hamiltonian_cycle()
                        if(result == []):
                            print("\nThere is no Hamiltonian cycle.")
                        else:
                            print("\nHamiltonian cycle: ")
                            print("Edges: ")
                            for edge in result[:-1]:
                                print(str(edge) + " ->", end = " ")
                            print(str(result[-1]))


                case 3:
                    self._running = False

                case _:
                    print("\nUnknown input entered!")