
#include "IsBipartite.hpp"
namespace ariel {
    std::string IsBipartite::Execute(const ariel::Graph &g) {
        std::vector<int> colors(g.getNumVertices(), -1); // Initialize all colors to -1

        // Start BFS traversal from an arbitrary vertex
        for (size_t v = 0; v < g.getNumVertices(); ++v) {
            if (colors[v] == -1) {
                if (!colorGraphBFS(g, colors, v)) {
                    return "Graph is not bipartite ";
                }
            }
        }

        return FindPartition(colors); // Graph is bipartite
    }

    bool IsBipartite::colorGraphBFS(const Graph& g, std::vector<int>& colors, size_t start) {
        std::queue<size_t> q;
        q.push(start);
        colors[start] = 0; // Color the starting vertex

        while (!q.empty()) {
            size_t current = q.front();
            q.pop();

            // Iterate over neighbors of the current vertex
            for (size_t v=0; v<g.getNumVertices();v++) {
                // Check if neighbor v is not colored yet
                if (colors[v] == -1 && g.getEdgeWeight(current,v)!=0) {
                    // Color the neighbor with a different color than the current vertex
                    colors[v] = 1 - colors[current];
                    q.push(v);
                } else if (colors[v] == colors[current]) {
                    // If neighbor has the same color as the current vertex, graph is not bipartite
                    return false;
                }
            }
        }

        return true; // Graph is bipartite
    }




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
