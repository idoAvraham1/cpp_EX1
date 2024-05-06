
#include <vector>
#include <sstream>
#include "iostream"
#include <xmath.h>
#include "DetectCycle.hpp"

namespace ariel {

    /**
    * Executes the cycle detection algorithm on the given graph.
    * @param g The graph to detect cycles in.
    * @return A string describing the detected cycle, or a message indicating no cycle was found.
    */
    std::string DetectCycle::Execute(const Graph &g, bool onlyNegativeCycle) {
        // empty graph
        if (g.isEmpty())
            return "Graph is empty";

        if (onlyNegativeCycle)
            return detectNegativeCycle(g);

        return detectCycle(g);

    }

    /**
    * Detects cycles in the given graph using Depth-First Search (DFS).
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
    bool
    DetectCycle::detectCycleDfs(const Graph &g, int v, int parent, std::vector<bool> &visited, std::vector<int> &path) {
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



    std::string DetectCycle::detectNegativeCycle(const Graph &g) {
        // distances matrix
        std::vector<std::vector<int>> dist(g.V(), std::vector<int>(g.V(), INT_MAX));
        // predecessors matrix
        std::vector<std::vector<int>> pred(g.V(), std::vector<int>(g.V(), -1));


        initDistAndPred(g,dist,pred);


        // Floyd-Warshall algorithm
        for (int k = 0; k < g.V(); k++) {
            for (int i = 0; i < g.V(); i++) {
                for (int j = 0; j < g.V(); j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        // Update predecessor
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
        return hasNegativeCycle(g,dist,pred);
    }

    void DetectCycle::initDistAndPred(const Graph& g,std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& pred) {
        // init the dist and pred array according to the graph type
        switch (g.getGraphType()) {
            case GraphType::DIRECTED: {
                for (int i = 0; i < g.V(); i++) {
                    for (int j = 0; j < g.V(); j++) {

                        if (g.getEdgeWeight(i, j) != 0) {
                            dist[i][j] = g.getEdgeWeight(i, j);
                            pred[i][j] = i;
                        }
                    }
                }
                break;
            }
            case GraphType::UNDIRECTED:
                for (int i = 0; i < g.V(); i++) {
                    for (int j = i + 1; j < g.V(); j++) {
                        if (i == j) {
                            dist[i][j] = 0;
                        }
                        if (g.getEdgeWeight(i, j) != 0) {
                            dist[i][j] = g.getEdgeWeight(i, j);
                            dist[j][i] = g.getEdgeWeight(i, j); // For undirected graph
                            pred[i][j] = i;
                            pred[j][i] = j;
                        }
                    }
                }
                break;
        }
    }


    std::string DetectCycle::hasNegativeCycle(const Graph& g,std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& pred) {
        switch (g.getGraphType()) {
            case GraphType::DIRECTED: {
                for (int i = 0; i < g.V(); i++) {
                    if (dist[i][i] < 0) {   // Negative cycle found, reconstruct the cycle
                        std::stringstream cycle;
                        int cur = i;
                        do {
                            cycle << cur << " -> ";
                            cur = pred[cur][cur];
                        } while (cur != i);   //
                        cycle << i; // Close the cycle
                        return "Negative cycle found: " + cycle.str();
                    }
                }
                break;
            }
            case GraphType::UNDIRECTED: {
                for (int i = 0; i < g.V(); i++) {
                    if (dist[i][i] < 0) {   // Negative cycle found, reconstruct the cycle
                        std::stringstream cycle;
                        int cur = i;
                        std::vector<bool> visited(g.V(), false); // To mark visited nodes
                        do {
                            visited[cur] = true;
                            cycle << cur << " -> ";
                            cur = pred[cur][cur]; // Move to the predecessor of cur
                        } while (cur != i && !visited[cur]);   // Continue until we reach the starting node or a visited node
                        cycle << i; // Close the cycle
                        return "Negative cycle found: " + cycle.str();
                    }
                }
                break;
            }
        }
        return "No negative cycle in the graph";
    }



}
    /*
     *    // get a new graph with extra vertex with outgoing edge to each vertex
          Graph new_Graph = g.addVertexWithEdges();

              // use bellman ford to find the shortest path to each vertex ( Execute invoke bellman ford)
              std::string ans = ShortestPath::Execute(new_Graph,g.V(), 0);
              // negative cycle detected
              if (ans.find("Negative cycle detected:") != std::string::npos)
                  return ans;
          return "No negative cycle in the graph";
     *
     *
     */

