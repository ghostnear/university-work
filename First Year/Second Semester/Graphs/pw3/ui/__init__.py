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
        print("1. Create empty graph.")
        print("2. Read graph from a file.")
        print("3. Write graph to a file.")
        print("4. Generate a random graph.")
        print("5. Find the shortest path between 2 vertices.")
        print("6. Find the cheapest path between 2 vertices.")
        print("7. Exit\n")

    def start(self):
        while self._running:
            self._print_menu()
            result = self._read_integer("Action > ")
            match result:
                case 1:
                    vertices = self._read_integer("Vertices: ")
                    self._currentGraph = Graph(vertices)

                case 2:
                    path = self._read_string("Path: ")
                    self._currentGraph = read_graph_from_file(path)

                case 3:
                    path = self._read_string("Path: ")
                    write_graph_to_file(path, self._currentGraph)

                case 4:
                    vertices = self._read_integer("Vertices: ")
                    edges = self._read_integer("Edges: ")
                    try:
                        self._currentGraph = generate_random_graph(vertices, edges)
                    except:
                        print("Could not generate a graph with the specified ammount of vertices and edges.")

                case 5:
                    if not self._currentGraph.is_vertex(0):
                        print("\nGraph is empty!")
                    else:
                        start = -1
                        end = -1
                        valid = False

                        while not valid:   
                            start = self._read_integer("\nStart vertex: ")
                            end = self._read_integer("End vertex: ")
                            valid = True

                            try:
                                result = self._currentGraph.shortest_path(start, end)

                                if(result == []):
                                    print("\nThere is no path between the specified vertices!")
                                else:
                                    print("\nShortest path is: ")
                                    for value in result[:-1]:
                                        print(value, end = " -> ")
                                    print(result[-1])
                                    print("Path length is:", len(result))
                            except:
                                print("\nInvalid vertices as input, try again!")
                                valid = False
            
                case 6:
                    if not self._currentGraph.is_vertex(0):
                        print("\nGraph is empty!")
                    else:
                        start = -1
                        end = -1
                        valid = False

                        while not valid:   
                            start = self._read_integer("\nStart vertex: ")
                            end = self._read_integer("End vertex: ")
                            valid = True

                            try:
                                [cost, result] = self._currentGraph.cheapest_path(start, end) 

                                if(result == [] or cost == float('inf')):
                                    print("\nThere is no path between the specified vertices!")
                                else:
                                    print("\nCheapest path is: ")
                                    for value in range(len(result) - 1):
                                        print(result[value], end = " -(")
                                        print(self._currentGraph.get_cost(result[value], result[value + 1]), end = ")-> ")
                                    print(result[-1])
                                    print("Path length is:", len(result))
                                    print("Path total cost is:", cost)
                            except:
                                print("\nInvalid vertices as input, try again!")
                                valid = False

                case 7:
                    self._running = False

                case _:
                    print("\nUnknown input entered!")