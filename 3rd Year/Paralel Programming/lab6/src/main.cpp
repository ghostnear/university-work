#include <iostream>
#include <vector>
#include <atomic>
#include <mutex>
#include <fstream>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include "threadpool.hpp"

class Graph
{
public:
    Graph();
    bool findHamiltonianCycle(int startVertex);
    void loadFromFile(const std::string& filename);
    int getVertices() const { return vertices; }

private:
    int vertices = 0;
    std::vector<std::unordered_set<int>> adjList;
    std::atomic<bool> found;
    std::vector<int> finalPath;
    std::mutex pathMutex;
    ThreadPool threadPool;

    void parallelDFS(int currentVertex, std::vector<bool> visited, std::vector<int> path, int depth);
};

Graph::Graph() : found(false), threadPool(std::thread::hardware_concurrency()) {}

void Graph::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    int edges;
    file >> vertices >> edges;
    adjList.resize(vertices);

    int v, w;
    for (int index = 0; index < edges; index++)
    {
        file >> v >> w;
        adjList[v].insert(w);
    }
    file.close();
}

bool Graph::findHamiltonianCycle(int startVertex)
{
    std::vector<bool> visited(vertices, false);
    std::vector<int> path(vertices, -1);
    path[0] = startVertex;
    visited[startVertex] = true;

    threadPool.enqueue([this, startVertex, visited, path, depth = 1]() mutable {
        parallelDFS(startVertex, visited, path, depth);
    });
    threadPool.wait();

    if (found.load())
    {
        std::cout << "Hamiltonian Cycle found:\n";
        for (int v : finalPath)
        {
            if (v == -1) break;
            std::cout << v << " -> ";
        }
        std::cout << finalPath[0] << "\n";
        return true;
    }

    std::cout << "No Hamiltonian Cycle found!" << std::endl;
    return false;
}

void Graph::parallelDFS(int currentVertex, std::vector<bool> visited, std::vector<int> path, int depth)
{
    if (found.load()) return;

    if(depth == vertices)
    {
        if (adjList[currentVertex].find(path[0]) != adjList[currentVertex].end())
        {
            std::lock_guard<std::mutex> lock(pathMutex);
            finalPath = path;
            found.store(true);
        }
        return;
    }

    for(int neighbor : adjList[currentVertex])
        if (!visited[neighbor] && !found.load())
        {
            visited[neighbor] = true;
            path[depth] = neighbor;

            threadPool.enqueue([this, neighbor, visited, path, depth = depth + 1]() mutable {
                parallelDFS(neighbor, visited, path, depth);
            });

            visited[neighbor] = false;
        }
}

int main()
{
    Graph g;
    g.loadFromFile("graph.txt");

    // Start from random vertice.
    srand(time(NULL));
    g.findHamiltonianCycle(rand() % g.getVertices());
    return 0;
}
