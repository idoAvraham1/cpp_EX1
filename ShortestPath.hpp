#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include "Graph.hpp"

#include <vector>
#include <queue>
#include <limits>
#include <sstream>

namespace ariel {
    class ShortestPath {
    public:
        static std::string Execute(const ariel::Graph &g, size_t source, size_t dest);

    private:
        // check weather the input is valid
        static bool isValidInput (const Graph& g, size_t source, size_t dest);
        // Dijkstra's algorithm for finding the shortest paths in weighted graphs
        static std::string dijkstra(const Graph& g, size_t source, size_t dest);

        // Bellman-Ford algorithm for finding the shortest paths, can handle graphs with negative weights
        static std::string bellmanFord(const Graph& g, size_t source, size_t dest);

        // BFS for finding the shortest paths in unweighted graphs or checking graph connectivity
        static std::string bfs(const Graph& g, size_t source, size_t dest);

        // Helper method to construct the path from the vector of predecessors
        static std::string constructPath(const std::vector<size_t>& predecessors, size_t source, size_t dest);
    };
}

#endif // SHORTEST_PATH_HPP
