import copy
import random

RANDOM_GRAPH_MAX_COST = 100

class Graph:
    _inbound : list
    _outbound : list
    _costs : list

    def __init__(self, verticesCount : int):
        self._inbound = {}
        self._outbound = {}
        self._costs = {}
        for vertex in range(verticesCount):
            self._inbound[vertex] = []
            self._outbound[vertex] = []

    """
        :returns The number of vertices of the graph.
    """
    def get_vertices_count(self) -> int:
        return len(self._inbound)

    """
        :returns The number of edges of the graph.
    """
    def get_edge_count(self) -> int:
        return len(self._costs)

    """
        :returns The list of vertices of the graph.
    """
    def parse_vertices(self) -> list:
        return list(range(self.get_vertices_count()))

    """
        :vertex The vertex for which to get the neighbours.
            :precondition: Must be a vertex of the graph.
        :returns The inbound neighbours of that vertex.
    """
    def parse_inbound_neighbours(self, vertex : int) -> list:
        if not self.is_vertex(vertex):
            raise Exception()
        return self._inbound[vertex][:]

    """
        :vertex The vertex for which to get the neighbours.
            :precondition: Must be a vertex of the graph.
        :returns The outbound neighbours of that vertex.
    """
    def parse_outbound_neighbours(self, vertex : int) -> list:
        if not self.is_vertex(vertex):
            raise Exception()
        return self._outbound[vertex][:]

    """
        :vertex The vertex for which to get the edges.
            :precondition: Must be a vertex of the graph.
        :returns The inbound edges of that vertex.
    """
    def parse_inbound_edges(self, vertex : int) -> list:
        if not self.is_vertex(vertex):
            raise Exception()
        return [(neighbour, vertex) for neighbour in self._inbound[vertex]]

    """
        :vertex The vertex for which to get the edges.
            :precondition: Must be a vertex of the graph.
        :returns The outbound edges of that vertex.
    """
    def parse_outbound_edges(self, vertex : int) -> list:
        if not self.is_vertex(vertex):
            raise Exception()
        return [(vertex, neighbour) for neighbour in self._outbound[vertex]]

    """
        :vertex The vertex for which to get the degree.
            :precondition: Must be a vertex of the graph.
        :returns The in degree of that vertex.
    """
    def in_degree(self, vertex : int) -> int:
        if not self.is_vertex(vertex):
            raise Exception()
        return len(self._inbound[vertex])

    """
        :vertex The vertex for which to get the degree.
            :precondition: Must be a vertex of the graph.
        :returns The out degree of that vertex.
    """
    def out_degree(self, vertex : int) -> int:
        if not self.is_vertex(vertex):
            raise Exception()
        return len(self._outbound[vertex])

    """
        Adds the specified vertex to the graph.
        :vertex The vertex that needs adding.
    """
    def add_vertex(self, vertex : int):
        # Shift inbound and outbounds.
        for index in reversed(range(vertex, self.get_vertices_count())):
            self._inbound[index + 1] = self._inbound[index][:]
            self._outbound[index + 1] = self._outbound[index][:]

        for index in range(self.get_vertices_count()):
            for key, value in enumerate(self._inbound[index]):
                if value >= vertex:
                    self._inbound[index][key] += 1
    
        for index in range(self.get_vertices_count()):
            for key, value in enumerate(self._outbound[index]):
                if value >= vertex:
                    self._outbound[index][key] += 1
        
        self._inbound[index] = []
        self._outbound[index] = []

        # Change costs.
        newCosts = {}
        for (start, end) in self._costs:
            cost = self._costs[(start, end)]
            if start >= vertex:
                start += 1
            if end >= vertex:
                end += 1
            newCosts[(start, end)] = cost
        self._costs = newCosts

    """
        Removes the specified vertex from the graph.
            :precondition: Must be a vertex of the graph.
        :vertex The vertex that needs removing.
    """
    def remove_vertex(self, vertex : int) -> int:
        if not self.is_vertex(vertex):
            raise Exception()

        # Shift inbound and outbounds.
        verticeCount = self.get_vertices_count()
        for index in range(vertex, verticeCount - 1):
            self._inbound[index] = self._inbound[index + 1][:]
            self._outbound[index] = self._outbound[index + 1][:]

        del self._inbound[verticeCount - 1]
        del self._outbound[verticeCount - 1]

        for index in range(self.get_vertices_count()):
            for key, value in enumerate(self._inbound[index]):
                if value > vertex:
                    self._inbound[index][key] -= 1
                elif value == vertex:
                    del self._inbound[index][key]
    
        for index in range(self.get_vertices_count()):
            for key, value in enumerate(self._outbound[index]):
                if value > vertex:
                    self._outbound[index][key] -= 1
                elif value == vertex:
                    del self._outbound[index][key]

        # Change costs.
        newCosts = {}
        for (start, end) in self._costs:
            cost = self._costs[(start, end)]
            if start != vertex and end != vertex:
                if start > vertex:
                    start -= 1
                if end > vertex:
                    end -= 1
                newCosts[(start, end)] = cost
        self._costs = newCosts

    """
        Adds the specified edge with the specified cost to the graph.
        :source The source of the edge.
            :precondition: Must be a vertex of the graph.
        :target The target of the edge.
            :precondition: Must be a vertex of the graph.
        :cost   The cost of the edge.
    """
    def add_edge(self, source : int, target : int, cost : int):
        if not self.is_vertex(source) or not self.is_vertex(target) or self.is_edge(source, target):
            raise Exception()

        self._inbound[target].append(source)
        self._outbound[source].append(target)
        self._costs[(source, target)] = cost

    """
        Removes the specified edge from the graph.
        :source The source of the edge.
            :precondition: Must be a vertex of the graph.
        :target The target of the edge.
            :precondition: Must be a vertex of the graph.
    """
    def remove_edge(self, source : int, target : int):
        if not self.is_vertex(source) or not self.is_vertex(target) or not self.is_edge(source, target):
            raise Exception()

        self._inbound[target].remove(source)
        self._outbound[source].remove(target)
        self._costs.remove((target, source))

    """
        Checks if there is an edge between the source and the target.
        :source The source of the possible edge.
            :precondition: Must be a vertex of the graph.
        :target The target of the possible edge.
            :precondition: Must be a vertex of the graph.
        :returns True if there is an edge, false otherwise.
    """
    def is_edge(self, source : int, target : int) -> bool:
        if not self.is_vertex(source) or not self.is_vertex(target):
            raise Exception()

        return (target in self._outbound[source])

    """
        Checks if the vertex exists.
        :vertex The possible vertex.
        :returns True if the vertex exists, false otherwise.
    """ 
    def is_vertex(self, vertex : int) -> bool:
        return vertex < len(self._inbound)

    """
        Sets the cost of the specified edge.
        :source The source of the possible edge.
            :precondition: Must be a vertex of the graph.
        :target The target of the possible edge.
            :precondition: Must be a vertex of the graph.
        :cost   The new cost of the possible edge.
    """ 
    def set_cost(self, source : int, target : int, cost : int):
        if not self.is_vertex(source) or not self.is_vertex(target) or not self.is_edge(source, target):
            raise Exception()

        self._costs[(source, target)] = cost

    """
        Gets the cost of the specified edge.
        :source The source of the possible edge.
            :precondition: Must be a vertex of the graph.
        :target The target of the possible edge.
            :precondition: Must be a vertex of the graph.
        :returns The cost of the possible edge.
    """ 
    def get_cost(self, source : int, target : int) -> int:
        if not self.is_vertex(source) or not self.is_vertex(target) or not self.is_edge(source, target):
            raise Exception()

        return self._costs[(source, target)]

    """
        :returns a deep copy of the graph.
    """
    def copy_graph(self):
        return copy.deepcopy(self)

def read_graph_from_file(path : str) -> Graph:
    with(open(path, "r") as file):
        lines = file.readlines()
        [vertices, edges] =  [int(element) for element in lines[0].split(' ')]

        result = Graph(vertices)
        for index in range(1, edges + 1):
            result.add_edge(*[int(element) for element in lines[index].split(' ')])
        
        file.close()
        return result

def write_graph_to_file(path : str, graph : Graph):
    with(open(path, "w") as file):
        file.write(str(graph.get_vertices_count()) + " " + str(graph.get_edge_count()) + "\n")
        for source in graph.parse_vertices():
            destinations = graph.parse_outbound_neighbours(source)
            for destination in destinations:
                file.write(str(source) + " " + str(destination) + " " + str(graph.get_cost(source, destination)) + "\n")
        file.close()

def generate_random_graph(verticeCount : int, edgeCount : int) -> Graph:
    if edgeCount > verticeCount * verticeCount:
        raise Exception()

    result = Graph(verticeCount)

    for index in range(edgeCount):
        (source, target, cost) = (random.randint(0, verticeCount - 1), random.randint(0, verticeCount - 1), random.randint(0, RANDOM_GRAPH_MAX_COST))
        while result.is_edge(source, target):
            (source, target, cost) = (random.randint(0, verticeCount - 1), random.randint(0, verticeCount - 1), random.randint(0, RANDOM_GRAPH_MAX_COST))
        result.add_edge(source, target, cost)

    return result
