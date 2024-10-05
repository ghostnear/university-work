import copy
import random

RANDOM_GRAPH_MAX_COST = 100

class Graph:
    _connected : list

    def __init__(self, verticesCount : int):
        self._connected = []
        for i in range(verticesCount):
            self._connected.append([])

    """
        :returns The number of vertices of the graph.
    """
    def get_vertices_count(self) -> int:
        return len(self._connected)

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
        Adds the specified edge to the graph.
        :source The source of the edge.
            :precondition: Must be a vertex of the graph.
        :target The target of the edge.
            :precondition: Must be a vertex of the graph.
    """
    def add_edge(self, source : int, target : int):
        if not self.is_vertex(source) or not self.is_vertex(target) or self.is_edge(source, target):
            raise Exception()

        self._connected[target].append(source)
        self._connected[source].append(target)

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
        :returns a hamiltonian cycle if it exists, [] otherwise.
    """
    def _hamiltonian_cycle(self):
        # We'll always start from 0.
        queue = [[0]]
        while queue != []:
            currentPath = queue.pop(0)
            currentVertex = currentPath[-1]
            for neighbour in self._connected[currentVertex]:
                if neighbour == 0:
                    if len(currentPath) == self.get_vertices_count():
                        return currentPath
                elif neighbour not in currentPath:
                    queue.append(currentPath + [neighbour])
        return []

def read_graph_from_file(path : str) -> Graph:
    with(open(path, "r") as file):
        lines = file.readlines()
        [vertices, edges] =  [int(element) for element in lines[0].split(' ')]

        result = Graph(vertices)
        for index in range(1, edges + 1):
            result.add_edge(*[int(element) for element in lines[index].split(' ')])
        
        file.close()
        return result