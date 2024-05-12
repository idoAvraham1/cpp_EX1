//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#include "DetectCycle.hpp"

namespace ariel {

    /**
    * Executes the cycle detection algorithm on the given graph.
    * @param g The graph to detect cycles in.
    * @return A string describing the detected cycle, or a message indicating no cycle was found.
    */
    std::string DetectCycle::Execute(const Graph &g) {
        // empty graph
        if (g.isEmpty())
            return "Graph is empty";
        return detectCycle(g);

    }

    /**
    * Detects cycles in the given graph using Depth-First Search (DFS).
    * the general strategy is to seek for a back edge.
    * @param g The graph to detect cycles in.
    * @return A string describing the detected cycle, or a message indicating no cycle was found.
    */
    std::string DetectCycle::detectCycle(const Graph &g) {
        // Initialize vectors to track visited vertices and recursion stack
        std::vector<bool> visited(g.V(), false);
        std::vector<int> path; // To store the current path

        // Iterate through all vertices and perform DFS to detect cycles
        for (int v = 0; v < g.V(); ++v) {
            if (!visited[v]) {
                if (detectCycleDfs(g, v, -1, visited, path))
                    return constructCycleString(path);
            }
        }

        // If no cycle is found, return a message indicating so
        return "No cycle found";
    }

    /**
       * Depth-First Search (DFS) traversal to detect cycles in the graph starting from a given vertex.
       * @param g The graph to detect cycles in.
       * @param v The current vertex being explored.
       * @param parent The parent vertex of the current vertex.
       * @param visited A vector to track visited vertices.
       * @param path A vector to store the current path during traversal.
       * @return True if a cycle is found, false otherwise.
       */
    bool DetectCycle::detectCycleDfs(const Graph &g, int v, int parent, std::vector<bool> &visited, std::vector<int> &path) {
        visited[v] = true;
        path.push_back(v);

        // Explore all neighbors of vertex v
        for (int neighbor = 0; neighbor < g.V(); ++neighbor) {
            int weight = g.getEdgeWeight(v, neighbor);
            if (weight != 0) {

                // For undirected graphs, ignore the edge to the parent
                if (g.getGraphType() == GraphType::UNDIRECTED) {
                    if (neighbor == parent)
                        continue;
                }
                // If the neighbor is already in the path, a cycle is found
                bool inPath = false;
                for (int i: path) {
                    if (i == neighbor) {
                        inPath = true;
                        break;
                    }
                }
                if (inPath) {
                    path.push_back(neighbor); // Include the neighbor to complete the cycle
                    return true;
                }
                // If the neighbor has not been visited yet, explore it recursively
                if (!visited[neighbor] && detectCycleDfs(g, neighbor, v, visited, path))
                    return true;
            }
        }

        // Remove v from the current path as we backtrack
        path.pop_back();
        return false;
    }


    // Constructs a string representation of the detected cycle.
    std::string DetectCycle::constructCycleString(const std::vector<int> &path) {
        // Construct the cycle string from the path
        std::stringstream ss;
        ss << "Cycle found: ";
        for (int i = 0; i < path.size(); ++i) {
            ss << path[i];
            if (i < path.size() - 1)
                ss << "->";
        }
        return ss.str();
    }

}//name space ariel


