//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com

#include "ShortestPath.hpp"

namespace ariel {

    /**
     * Finds the shortest path between two vertices in a graph.
     * Uses different algorithms based on the type of the graph.
     * @param g The graph in which to find the shortest path.
     * @param source The source vertex.
     * @param dest The destination vertex.
     * @return A string describing the shortest path, or an error message if no path exists or input is invalid.
     */
    std::string ShortestPath::Execute(const ariel::Graph &g, size_t source, size_t dest) {
        std::vector<size_t> shortestPath;
        if (!isValidInput(g, source, dest))
             throw std::invalid_argument("Invalid input for finding shortest path");

        switch (g.getEdgeNegativity()) {
            case EdgeNegativity::NEGATIVE:
                // Use Bellman-Ford algorithm for graphs with negative weights
                return bellmanFordSetUps(g,source,dest);
            default:
                // Check for unweighted, weighted, or unknown graphs
                switch (g.getEdgeType()) {
                    case EdgeType::WEIGHTED:
                        // Use Dijkstra's algorithm for weighted graphs with non-negative weights
                        shortestPath = dijkstra(g, source, dest);
                        break;
                    case EdgeType::UNWEIGHTED:
                        // Use BFS for unweighted graphs
                        shortestPath = bfs(g, source, dest);
                        break;
                    default:
                        // Handle unknown edge types
                        throw std::runtime_error("Unknown graph type encountered");
                }
        }
        // check if a path was found
        if( shortestPath.empty())
            return "There is no path from " + std::to_string(source) + " to " + std::to_string(dest);

        return constructPath(shortestPath,source,dest);
    }


    // finding the shortest path from source to dest using dijkstra's algorithm
    std::vector<size_t> ShortestPath::dijkstra(const Graph &g, size_t source, size_t dest) {
        // init the predecessors array to infinity to indicate no pred
        std::vector<size_t> predecessors(g.V(), std::numeric_limits<size_t>::max());
        // init the distance array to infinity for each vertex
        std::vector<int> dist(g.V(), std::numeric_limits<int>::max());
        dist[source] = 0;
        // create a priority que to store the distance from source of each vertex
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>,
                std::greater<>> pq;
        // insert source vertex with distance 0 to the pq
        pq.emplace(0, source);

        while (!pq.empty()) {
            //extract the vertex with the min distance
            int dist_u = pq.top().first;
            size_t u = pq.top().second;
            pq.pop();

            // relax all the adj of u if necessary
            for (size_t v = 0; v < g.V(); v++) {

                int weight_uv = g.getEdgeWeight(u, v);

                if (weight_uv != 0) {
                    if (dist[v] > dist_u + weight_uv) {
                        dist[v] = dist_u + weight_uv;
                        predecessors[v] = u;
                        pq.emplace(dist[v], v);
                    }
                }
            }
        }
        // check if there is path
        if (predecessors[dest] == std::numeric_limits<size_t>::max())
            return {};


        return buildShortestPath(g,dist,source,dest);

    }

    // finding the shortest path from source to dest using bellman-ford's algorithm
    std::vector<size_t> ShortestPath::bellmanFord(const Graph &g, size_t source, size_t dest) {
        // Initialize predecessors with a special value (-1) to indicate no predecessor
        std::vector<size_t > predecessors(g.V(), size_t(-1));
        // Initialize distances with infinity
        std::vector<int> dist(g.V(), std::numeric_limits<int>::max());
        dist[source] = 0;

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
        // Check for negative cycles according to the graph type
        for (size_t u = 0; u < g.V(); ++u) {
            for (size_t v = 0; v < g.V(); ++v) {
                int weight_uv = g.getEdgeWeight(u, v);
                if (weight_uv != 0 &&  dist[u] != std::numeric_limits<int>::max()  && dist[u] + weight_uv < dist[v] ) {

                    // ignore negative cycle with size 1 in undirected graphs
                    if(g.getGraphType()==GraphType::UNDIRECTED && predecessors[u] == v)
                        continue;

                    // Negative cycle detected
                    throw std::invalid_argument("Negative cycle detected in the graph");
                }
            }
        }
        // return the shortest path vector
        return buildShortestPath(g,dist,source,dest);

    }

    // finding the shortest path from source to dest using bds
    std::vector<size_t> ShortestPath::bfs(const Graph &g, size_t source, size_t dest) {
        // Array of the parent of each node
        std::vector<size_t> parents(g.V(), std::numeric_limits<size_t>::max());
        // Array to indicate if a node was visited during the traversal
        std::vector<bool> visited(g.V(), false);
        std::queue<size_t> q;

        visited[source] = true;
        q.push(source);

        while (!q.empty()) {
            size_t current = q.front();
            q.pop();

            // Check if the destination vertex is reached
            if (current == dest) {
                break; // Stop BFS traversal
            }

            // Enqueue neighboring vertices
            for (size_t neighbor = 0; neighbor < g.V(); ++neighbor) {
                if (!visited[neighbor] && g.getEdgeWeight(current, neighbor) != 0) {
                    visited[neighbor] = true;
                    parents[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
        // Check if the destination vertex was reached
        if (parents[dest] == std::numeric_limits<size_t>::max()) {
            return {}; // Return an empty vector if no path exists
        }

        // Reconstruct the shortest path using the parent's array
        std::vector<size_t> shortestPath;
        size_t currentVertex = dest;

        // Reconstruct the shortest path by backtracking from the destination to the source
        while (currentVertex != source) {
            shortestPath.push_back(currentVertex);
            currentVertex = parents[currentVertex];
        }
        shortestPath.push_back(source);

        // Reverse the path to get it in the correct order (from source to destination)
        std::reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }

    // Checks if the input parameters are valid for finding the shortest path.
    bool ShortestPath::isValidInput(const Graph &g, size_t source, size_t dest) {
        size_t V = g.V();

        // Check if the graph is empty
        if (g.isEmpty()) {
            return false; // Empty graph
        }

        // Check if source or destination vertices are out of range
        if (source >= V || dest >= V) {
            return false; // Source or destination vertex out of range
        }

        return true; // Valid input
    }

    std::string ShortestPath::bellmanFordSetUps(const Graph &g, size_t source, size_t dest) {

        // find the shortest path from source vx to the dest vx
        std::vector<size_t> pathFromSourceToDest= bellmanFord(g,source,dest);

         if( pathFromSourceToDest.empty())
            return "There is no path from " + std::to_string(source) + " to " + std::to_string(dest);

        if(g.getGraphType() == GraphType::DIRECTED)
            return constructPath(pathFromSourceToDest,source,dest);

        // handle undirected graphs
        else {
            // find the shortest path from dest vx to the source vx
            std::vector<size_t> pathFromDestToSource = bellmanFord(g, dest, source);

            // find the cheaper path, and return it
            int weightFromSourceToDest = CalculatePathCost(pathFromSourceToDest, g);
            int weightFromDestToSource = CalculatePathCost(pathFromDestToSource, g);

            if (weightFromSourceToDest < weightFromDestToSource)
                return constructPath(pathFromSourceToDest,source,dest);

            reverse(pathFromDestToSource.begin(), pathFromDestToSource.end());
            return constructPath(pathFromDestToSource, dest , source);
        }

    }

    std::string ShortestPath::constructPath(const std::vector<size_t> &path,size_t source, size_t dest) {
        std::string pathAsString = std::to_string(path.at(0));
        for (size_t i = 1; i < path.size(); ++i) {
            pathAsString += "->" + std::to_string(path.at(i));
        }
        return "Shortest path from " + std::to_string(source) + " to " + std::to_string(dest) + " is: " + pathAsString;
    }

    int ShortestPath::CalculatePathCost(std::vector<size_t> &path, const Graph &g) {
        int totalCost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int current_Edge = g.getEdgeWeight(path[i],path[i+1]);
            totalCost += current_Edge;
        }
        return totalCost;
    }

    std::vector<size_t> ShortestPath::buildShortestPath(const Graph &g, std::vector<int> &dist ,  size_t source ,size_t dest) {
        // Build the shortest path vector
        std::vector<size_t> shortestPath;
        size_t currentVertex = dest;
        while (currentVertex != source) {
            shortestPath.push_back(currentVertex);
            for (size_t u = 0; u < g.V(); ++u) {
                int Edge_u_current =g.getEdgeWeight(u,size_t(currentVertex));
                if (Edge_u_current != 0 &&
                    dist[u] + Edge_u_current == dist[size_t(currentVertex)]) {
                    currentVertex = u;
                    break;
                }
            }
        }
        shortestPath.push_back(source);
        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }


}// namespace ariel