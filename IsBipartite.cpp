
#include "IsBipartite.hpp"
namespace ariel {

    /**
     * Determines whether the graph is bipartite or not.
     * @param g The graph to check for bipartite.
     * @return A string describing the bipartite partitioning of the graph, or an error message if the graph is not bipartite.
     */
    std::string IsBipartite::Execute(const ariel::Graph &g) {
        // empty graph
        if(g.isEmpty())
            return "Graph is empty";

        std::vector<int> colors(g.V(), -1); // Initialize all colors to -1

        // Start BFS traversal from an arbitrary vertex
        for (size_t v = 0; v < g.V(); ++v) {
            if (colors[v] == -1) {
                if (!colorGraphBFS(g, colors, v)) {
                    return "Graph is not bipartite ";
                }
            }
        }

        return FindPartition(colors); // Graph is bipartite
    }

    /**
     * Colors the graph vertices using Breadth-First Search (BFS) traversal to determine bipartiteness.
     * @param g The graph to be colored.
     * @param colors A vector to store the color of each vertex.
     * @param start The starting vertex for BFS traversal.
     * @return True if the graph is bipartite, false otherwise.
     */
    bool IsBipartite::colorGraphBFS(const Graph& g, std::vector<int>& colors, size_t start) {
        std::queue<size_t> q;
        q.push(start);
        colors[start] = 0; // Color the starting vertex

        while (!q.empty()) {
            size_t current = q.front();
            q.pop();

            // Iterate over neighbors of the current vertex
            for (size_t v = 0; v < g.V(); ++v) {
                // Check if there is an edge between current and v
                if (g.getEdgeWeight(current, v) != 0) {
                    // Check if neighbor v is not colored yet
                    if (colors[v] == -1) {
                        // Color the neighbor with a different color than the current vertex
                        colors[v] = 1 - colors[current];
                        q.push(v);
                    } else if (colors[v] == colors[current]) {
                        // If neighbor has the same color as the current vertex, graph is not bipartite
                        return false;
                    }
                }
            }
        }

        return true; // Graph is bipartite
    }



    /**
     * Finds the partitioning of the bipartite graph into two sets.
     * @param colors A vector containing the color of each vertex.
     * @return A string representing the bipartite partitioning of the graph.
     */
    std::string IsBipartite::FindPartition(std::vector<int> &colors) {
        // init A and B
        std::vector<size_t> A, B;

        // Populate sets A and B based on colors
        for (size_t i = 0; i < colors.size(); ++i) {
            if (colors[i] == 0) {
                A.push_back(i);
            } else {
                B.push_back(i);
            }
        }

        // Now return the result in the desired format
        std::string result = "Graph is bipartite, A={";
        for (size_t i = 0; i < A.size(); ++i) {
            result += std::to_string(A[i]);
            if (i != A.size() - 1) result += ",";
        }
        result += "}, B={";
        for (size_t i = 0; i < B.size(); ++i) {
            result += std::to_string(B[i]);
            if (i != B.size() - 1) result += ",";
        }
        result += "}";

        return result;
    }
}
