#include <stack>
#include "ShortestPath.hpp"

#include "iostream"

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
         if( ! isValidInput(g, source, dest))
             return "inValid input for finding shortest path";

         switch (g.getEdgeNegativity()) {
             case EdgeNegativity::NEGATIVE:
                 // Use Bellman-Ford algorithm for graphs with negative weights
                 return bellmanFord(g, source, dest);
             default:
                 // Check for unweighted, weighted, or unknown graphs
                 switch (g.getEdgeType()) {
                     case EdgeType::WEIGHTED:
                         // Use Dijkstra's algorithm for weighted graphs with non-negative weights
                         return dijkstra(g, source, dest);
                     case EdgeType::UNWEIGHTED:
                         // Use BFS for unweighted graphs
                         return bfs(g, source, dest);
                     default:
                         // Handle unknown edge types
                         throw std::runtime_error("Unknown graph type encountered");
                 }
         }
     }


     std::string ShortestPath::dijkstra(const Graph &g, size_t source, size_t dest) {
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
         if (predecessors[dest] == std::numeric_limits<size_t>::max())
             return "there is no path from " + std::to_string(source) + "to" + std::to_string(dest);

         std::string path = constructPath(predecessors, source, dest);
         return "Shortest path from " + std::to_string(source) + " to " + std::to_string(dest) + " is: " + path;

     }

     std::string ShortestPath::bellmanFord(const Graph &g, size_t source, size_t dest) {
          // init the pred with infinity to indicate there is no pred
          std::vector<size_t> predecessors(g.V(), std::numeric_limits<size_t>::max());
          // init the distances with infinity
          std::vector<int> dist(g.V() , std::numeric_limits<int>::max());
          dist[source]=0;

          //repeat number of vertices-1  times:
          for(int i=0; i< g.V() - 1; i++){
              // iterate throw each edge in the graph
              for(size_t u=0; u< g.V(); u++){
                  for(size_t v=0; v< g.V(); v++){
                      // perform relax on the edge u,v
                      int weight_uv= g.getEdgeWeight(u,v);
                      // if the edge u,v exist && dist[u] has been updated at least once
                      if(dist[v]> weight_uv+dist[u] && weight_uv != 0 && dist[u] != std::numeric_limits<int>::max()){
                          dist[v]=weight_uv+dist[u];
                          predecessors[v]=u;
                      }
                  }
              }
          }

         // Check for negative cycles
         for (size_t u = 0; u < g.V(); ++u) {
             for (size_t v = 0; v < g.V(); ++v) {
                 int weight_uv = g.getEdgeWeight(u, v);
                 if (weight_uv != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + weight_uv < dist[v]) {
                     // Negative cycle detected
                     return "Negative cycle detected in the graph";
                 }
             }
         }
         if (predecessors[dest] == std::numeric_limits<size_t>::max())
             return "there is no path from " + std::to_string(source) + "to" + std::to_string(dest);


         std::string path = constructPath(predecessors, source, dest);
         return "Shortest path from " + std::to_string(source) + " to " + std::to_string(dest) + " is: " + path;
     }

     std::string ShortestPath::bfs(const Graph &g, size_t source, size_t dest) {
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
             return "There is no path from " + std::to_string(source) + " to " + std::to_string(dest);
         }

         // Reconstruct the shortest path using the parents array
         std::string path = constructPath(parents, source, dest);
         return "Shortest path from " + std::to_string(source) + " to " + std::to_string(dest) + " is: " + path;
     }


     std::string ShortestPath::constructPath(const std::vector<size_t> &predecessors, size_t source, size_t dest) {
         std::stack<size_t> pathStack;
         size_t current = dest;

         // Backtrack from the destination to the source vertex
         while (current != source) {
             pathStack.push(current);
             current = predecessors[current];
         }
         pathStack.push(source); // Add the source vertex to the stack

         // Construct the path string by popping elements from the stack
         std::stringstream path;
         while (!pathStack.empty()) {
             path << pathStack.top();
             pathStack.pop();
             if (!pathStack.empty()) {
                 path << " -> ";
             }
         }

         return path.str();
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


 }