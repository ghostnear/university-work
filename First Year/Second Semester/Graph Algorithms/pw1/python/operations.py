def parse_inbound_edges(graph : Graph, target : int) -> list:
    if not graph.is_vertex(target):
        raise Exception()

    return [(source, target) for source in graph._inbound[target]]

def parse_outbound_edges(graph : Graph, source : int) -> list:
    if not graph.is_vertex(target):
        raise Exception()

    return [(source, target) for target in graph._outbound[source]]