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
        print("2. Find the minimal spanning tree using Kruskal's algorithm.")
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
                        print("\nMinimal spanning tree: ")
                        [cost, result] = self._currentGraph._minimal_spanning_tree()
                        print("Cost: " + str(cost))
                        print("Edges: ")
                        for edge in result.get_edges():
                            print(str(edge[0]) + "-" + str(edge[1]) + " " + str(self._currentGraph.get_cost(edge[0], edge[1])))


                case 3:
                    self._running = False

                case _:
                    print("\nUnknown input entered!")