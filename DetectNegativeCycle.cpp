//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#include "DetectNegativeCycle.hpp"
namespace ariel {

    /**
    * Executes the negative cycle detection algorithm on the given graph.
    * @param g The graph on which to perform negative cycle detection.
    * @return A string indicating the presence or absence of negative cycles.
    */
    std::string DetectNegativeCycle::Execute(const ariel::Graph &g) {
        if (g.getEdgeNegativity() == EdgeNegativity::NONE)
            return "No negative cycle detected in the graph";

        return detectNegativeCycle(g);
    }

    /**
    * Detects negative cycles in the given graph using the Bellman-ford algorithm.
    * will use different approaches according to graph type
    * @param g The graph in which to detect negative cycles.
    * @return A string indicating the presence or absence of negative cycles.
    */
    std::string DetectNegativeCycle::detectNegativeCycle(const ariel::Graph &g) {

        // for directed graph, add a vertex with an outgoing edge to each vertex
        if ( g.getGraphType()==GraphType::DIRECTED) {
            // create a new graph g with new vertex
            Graph new_Graph = g.addVertexWithEdges();

            // run bellman-ford on the new graph from the new vertex
            return bellmanFord(new_Graph, new_Graph.V() - 1);

        }

        // for undirected graph run bellman-ford from each vertex
        else {
            for (size_t i = 0; i < g.V(); ++i) {
                std::string cycle = bellmanFord(g, i);
                if (cycle != "No negative cycle detected in the graph")
                    return cycle;
            }
        }
        return "No negative cycle detected in the graph";
    }


    // bellman ford algorithm for detecting negative cycles in the graphs
    std::string DetectNegativeCycle::bellmanFord(const Graph &g, size_t source) {
        // Initialize predecessors with a special value (-1) to indicate no predecessor
        std::vector<size_t> predecessors(g.V(), size_t(-1));
        // Initialize distances with infinity
        std::vector<int> dist(g.V(), std::numeric_limits<int>::max());
        dist[source] = 0;
        // Initialize a visited array to keep track of visited vertices
        std::vector<bool> visited(g.V(), false);

        size_t negativeCycleStart = g.V(); // Initialize to a value not in the graph
        // Iterating |V| - 1 times
        for (int i = 0; i < g.V() - 1; i++) {
            // Iterate through each edge in the graph
            for (size_t u = 0; u < g.V(); u++) {
                for (size_t v = 0; v < g.V(); v++) {
                    // Perform relaxation on the edge u,v
                    int weight_uv = g.getEdgeWeight(u, v);
                    // Relax the edge if it exists and a shorter path is found
                    if (weight_uv != 0 && dist[v] > weight_uv + dist[u] && dist[u] != std::numeric_limits<int>::max()) {
                        // in undirected graphs, use negative edge only once to relax
                        if(g.getGraphType()==GraphType::UNDIRECTED && predecessors[u] == v) {
                            continue;
                        }
                        dist[v] = weight_uv + dist[u];
                        predecessors[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles using the findNegativeCycle function
       return  findNegativeCycle(g, dist, predecessors);
    }

    // detect and construct the negative cycle in the graph if one was found
    std::string DetectNegativeCycle::findNegativeCycle(const Graph& g, std::vector<int>& dist, std::vector<size_t>& predecessors) {
        // Check for negative cycles
        for (size_t v = 0; v < g.V(); ++v) {
            for (size_t u = 0; u < g.V(); ++u) {
                int weight_uv = g.getEdgeWeight(u, v);
                    if (weight_uv != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + weight_uv < dist[v]) {
                        // ignore negative cycle with size 1 in undirected graphs
                        if (g.getGraphType() == GraphType::UNDIRECTED && predecessors[u] == v){
                            continue;
                        }
                        // Found a vertex involved in a negative cycle
                        size_t cycleStart = u;
                        std::string cycle = "Negative cycle found: ";
                        size_t current = cycleStart;

                        // Use a stack to reverse the cycle
                        std::stack<size_t> cycleStack;

                        // Traverse the cycle starting from the cycle start
                        do {
                            cycleStack.push(current);
                            current = predecessors[current];
                        } while (current != cycleStart);

                        // Add the cycle start to complete the cycle
                        cycle += std::to_string(cycleStart) + " -> ";

                        // Construct the cycle string by popping elements from the stack
                        while (!cycleStack.empty()) {
                            current = cycleStack.top();
                            cycleStack.pop();
                            cycle += std::to_string(current) + " -> ";
                        }

                        // Remove the last " -> " from the string
                        cycle.erase(cycle.length() - 4);

                        return cycle;
                    }
                }

        }

        return "No negative cycle detected in the graph";
    }

}// name space ariel


