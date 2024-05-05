#include <stdexcept>
#include "IsConnected.hpp"
#include <iostream>

namespace ariel {

    /**
     * Determines whether the graph is connected or not.
     * @param g The graph to check for connectivity.
     * @return True if the graph is connected, false otherwise.
     * @throws std::runtime_error if encountering an unknown graph type.
     */
    bool IsConnected::Execute(const ariel::Graph &g) {
        // empty graph
        if(g.isEmpty())
            return "Graph is empty";

        // Switch based on the type of graph (directed or undirected)
        switch (g.getGraphType()) {
            // For directed graph, use specialized function to check connectivity
            case(GraphType::DIRECTED):
                return isConnectedDirected(g);

                // For undirected graph, use specialized function to check connectivity
            case(GraphType::UNDIRECTED):
                return isConnectedUndirected(g);

                // Handle the case of encountering an unknown graph type
            default:
                throw std::runtime_error("Unknown graph type encountered");
        }
    }

    /**
      * Determines whether the undirected graph is connected using Depth-First Search (DFS).
      * @param g The undirected graph to check for connectivity.
      * @return True if the undirected graph is connected, false otherwise.
      */
    bool IsConnected::isConnectedUndirected(const ariel::Graph &g) {
        // Initialize a vector to track visited vertices during DFS
        std::vector<bool> visited(g.V(), false);

        // Start DFS from an arbitrary vertex (vertex 0)
        dfs(g, visited, 0);

        // Check if all vertices were visited during DFS
        for(size_t v = 0; v < g.V(); ++v)
            if(!visited[v])
                return false;
        return true;
    }

    /**
     * Determines whether the directed graph is strongly connected using two DFS traversals.
     * @param g The directed graph to check for strong connectivity.
     * @return True if the directed graph is strongly connected, false otherwise.
     *  took the idea from : https://www.geeksforgeeks.org/check-if-a-directed-graph-is-connected-or-not/
     */
    bool IsConnected::isConnectedDirected(const ariel::Graph &g) {
        // Initialize visited arrays for DFS traversal and reverse DFS traversal
        std::vector<bool> vis1(g.V(), false);
        std::vector<bool> vis2(g.V(), false);

        // Step 1: Run DFS from a random vertex and mark all visited vertices in vis1
        dfs(g, vis1, 0);
        // Check if all vertices are visited in vis1
        for (bool visited : vis1) {
            if (!visited)
                return false; // Not strongly connected
        }

        // Step 2: Reverse the direction of all edges in the graph
        ariel::Graph gReversed = g.getReversedGraph();

        // Step 3: Run DFS from the same random vertex in the reversed graph and mark all visited vertices in vis2
        dfs(gReversed, vis2, 0);

        // Step 4: Check if any vertex is not visited in vis2
        for (bool visited : vis2) {
            if (!visited)
                return false; // Not strongly connected
        }
        return true;
    }


    /**
     * Depth-First Search (DFS) traversal of the graph starting from a given vertex.
     * @param g The graph to perform DFS traversal on.
     * @param visited A vector indicating whether each vertex has been visited.
     * @param start The starting vertex for DFS traversal.
     */
    void IsConnected::dfs(const Graph &g, std::vector<bool>& visited, size_t start) {
        // Mark the current vertex as visited
        visited[start] = true;

        // Iterate over all adjacent vertices and recursively visit unvisited vertices
        for(size_t v = 0; v < g.V(); ++v){
            if(g.getEdgeWeight(start, v) != 0 && !visited[v])
                dfs(g, visited, v);
        }
    }
}
