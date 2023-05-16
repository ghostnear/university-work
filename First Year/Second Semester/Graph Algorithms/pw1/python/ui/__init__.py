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
        print("5. Do operations on the current graph.")
        print("6. Exit\n")

    def _print_operations(self):
        print("\nGraph Operations\n")
        print("1. Get vertices count.")
        print("2. Get edges count.")
        print("3. Parse inbound neighbours.")
        print("4. Parse outbound neighbours.")
        print("5. Parse inbound edges.")
        print("6. Parse outbound edges.")
        print("7. Get in degree of vertex.")
        print("8. Get out degree of vertex.")
        print("9. Add vertex.")
        print("10. Remove vertex.")
        print("11. Add edge.")
        print("12. Remove edge.")
        print("13. Set cost of edge.")
        print("14. Get cost of edge.")
        print("15. Go back.\n")

    def _run_operations(self):
        self._runningOperations = True
        while self._runningOperations:
            self._print_operations()
            result = self._read_integer("Action > ")
            match result:
                case 1:
                    print("Vertices count:", self._currentGraph.get_vertices_count())

                case 2:
                    print("Edge count:", self._currentGraph.get_edge_count())

                case 3:
                    vertex = self._read_integer("Vertex: ")
                    print("Inbound neighbours:", self._currentGraph.parse_inbound_neighbours(vertex))

                case 4:
                    vertex = self._read_integer("Vertex: ")
                    print("Outbound neighbours:", self._currentGraph.parse_outbound_neighbours(vertex))

                case 5:
                    vertex = self._read_integer("Vertex: ")
                    print("Inbound edges:", self._currentGraph.parse_inbound_edges(vertex))

                case 6:
                    vertex = self._read_integer("Vertex: ")
                    print("Outbound edges:", self._currentGraph.parse_outbound_edges(vertex))

                case 7:
                    vertex = self._read_integer("Vertex: ")
                    print("In degree:", self._currentGraph.in_degree(vertex))

                case 8:
                    vertex = self._read_integer("Vertex: ")
                    print("Out degree:", self._currentGraph.out_degree(vertex))

                case 9:
                    vertex = self._read_integer("Vertex: ")
                    try:
                        self._currentGraph.add_vertex(vertex)
                        print("Specified vertex added successfully.")
                    except Exception:
                        print("Could not add the specified vertex.")

                case 10:
                    vertex = self._read_integer("Vertex: ")
                    try:
                        self._currentGraph.remove_vertex(vertex)
                        print("Specified vertex removed successfully.")
                    except Exception:
                        print("Could not remove the specified vertex.")

                case 11:
                    source = self._read_integer("Source: ")
                    target = self._read_integer("Target: ")
                    cost = self._read_integer("Cost: ")
                    try:
                        self._currentGraph.add_edge(source, target, cost)
                        print("Specified edge added successfully.")
                    except Exception:
                        print("Could not add the specified edge.")

                case 12:
                    source = self._read_integer("Source: ")
                    target = self._read_integer("Target: ")
                    try:
                        self._currentGraph.remove_edge(source, target)
                        print("Specified edge removed successfully.")
                    except Exception:
                        print("Could not remove the specified edge.")

                case 13:
                    source = self._read_integer("Source: ")
                    target = self._read_integer("Target: ")
                    cost = self._read_integer("Cost: ")
                    try:
                       self._currentGraph.set_cost(source, target, cost)
                       print("Cost set successfully.")
                    except Exception:
                        print("Could not find the specified edge.")

                case 14:
                    source = self._read_integer("Source: ")
                    target = self._read_integer("Target: ")
                    try:
                        print("Cost", self._currentGraph.get_cost(source, target))
                    except Exception:
                        print("Could not find the specified edge.")

                case 15:
                    self._runningOperations = False

                case _:
                    print("\nUnknown input entered!")

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
                    self._run_operations()

                case 6:
                    self._running = False

                case _:
                    print("\nUnknown input entered!")
