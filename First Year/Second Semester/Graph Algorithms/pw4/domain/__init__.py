import copy
import random

RANDOM_GRAPH_MAX_COST = 100

class Graph:
    _connected : list
    _costs : dict

    def __init__(self, verticesCount : int):
        self._connected = []
        for i in range(verticesCount):
            self._connected.append([])
        self._costs = {}
        self._sortedCosts = []

    """
        :returns The number of vertices of the graph.
    """
    def get_vertices_count(self) -> int:
        return len(self._connected)

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
        :returns The connected neighbours of that vertex.
    """
    def parse_connected_edges(self, vertex : int) -> list:
        if not self.is_vertex(vertex):
            raise Exception()
        return self._connected[vertex][:]

    """
        :vertex The vertex for which to get the edges.
            :precondition: Must be a vertex of the graph.
        :returns The connected edges of that vertex.
    """
    def parse_connected_edges(self, vertex : int) -> list:
        if not self.is_vertex(vertex):
            raise Exception()
        return [(vertex, neighbour) for neighbour in self._connected[vertex]]

    """
        :vertex The vertex for which to get the degree.
            :precondition: Must be a vertex of the graph.
        :returns The degree of that vertex.
    """
    def degree(self, vertex : int) -> int:
        if not self.is_vertex(vertex):
            raise Exception()
        return len(self._connected[vertex])

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

        self._connected[target].append(source)
        self._connected[source].append(target)
        self.set_cost(source, target, cost)

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

        self._connected[target].remove(source)
        self._connected[source].remove(target)
        self._costs.remove((target, source))
        self._costs.remove((source, target))

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

        return (target in self._connected[source] or source in self._connected[target])

    """
        Checks if the vertex exists.
        :vertex The possible vertex.
        :returns True if the vertex exists, false otherwise.
    """ 
    def is_vertex(self, vertex : int) -> bool:
        return vertex < len(self._connected) and vertex >= 0

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
        self._costs[(target, source)] = cost

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
        Internally sorts the edges by cost.
    """
    def _sort_edges_by_cost(self):
        self._sortedCosts = sorted(self._costs, key = lambda edge : self._costs[edge])

    """
        :returns all the vertices in the graph.
    """
    def get_edges(self):
        for edge in self._costs:
            if edge[0] < edge[1]:
                yield edge
    
    """
        :returns the minimal spanning tree using Kruskal's algorithm.
    """
    def _minimal_spanning_tree(self):
        # Sort the edges by cost.
        self._sort_edges_by_cost()

        # Initialize the result.
        cost = 0
        result = Graph(self.get_vertices_count())
        parents = [i for i in range(self.get_vertices_count())]

        # Go through all the edges.
        for edge in self._sortedCosts:
            # Get the source and the target of the edge.
            source = edge[0]
            target = edge[1]
            edge_cost = self.get_cost(source, target)

            # If the source and the target are not in the same connected component and the edge was not already processed.
            if parents[source] != parents[target]:
                # Add the edge to the result.
                result.add_edge(source, target, edge_cost)
                cost += edge_cost

                # Merge the connected components.
                targetparent = parents[target]
                for vertex in range(self.get_vertices_count()):
                    if parents[vertex] == targetparent:
                        parents[vertex] = parents[source]

        return [cost, result]

def read_graph_from_file(path : str) -> Graph:
    with(open(path, "r") as file):
        lines = file.readlines()
        [vertices, edges] =  [int(element) for element in lines[0].split(' ')]

        result = Graph(vertices)
        for index in range(1, edges + 1):
            result.add_edge(*[int(element) for element in lines[index].split(' ')])
        
        file.close()
        return result