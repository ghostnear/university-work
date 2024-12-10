import random

def generate_hamiltonian_cycle_graph(num_vertices):
    # Start with a simple Hamiltonian cycle
    edges = [(i, (i + 1) % num_vertices) for i in range(num_vertices)]
    
    # Add some additional random edges to make the graph more complex
    additional_edges = num_vertices  # Add 'num_vertices' additional edges
    while additional_edges > 0:
        u = random.randint(0, num_vertices - 1)
        v = random.randint(0, num_vertices - 1)
        if u != v and (u, v) not in edges and (v, u) not in edges:
            edges.append((u, v))
            additional_edges -= 1

    # Shuffle the edges.
    random.shuffle(edges)
    
    return edges

def save_graph_to_file(edges, vertices, filename):
    with open(filename, 'w') as f:
        f.write(str(vertices) + ' '+ str(len(edges)) + '\n')
        for u, v in edges:
            f.write(str(u) + ' ' + str(v) + '\n')

def main():
    num_vertices = int(input("Enter the number of vertices: "))
    edges = generate_hamiltonian_cycle_graph(num_vertices)
    save_graph_to_file(edges, num_vertices, 'graph.txt')

if __name__ == "__main__":
    main()
