//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include "Graph.hpp"
#include <stack>
#include "iostream"
#include <vector>
#include <queue>
#include <limits>
#include <sstream>
#include <algorithm>

namespace ariel {
    class ShortestPath {
    public:
        static std::string Execute(const ariel::Graph &g, size_t source, size_t dest);

    private:

        static std::string bellmanFordSetUps(const Graph& g, size_t source, size_t dest);
        // check weather the input is valid
        static bool isValidInput (const Graph& g, size_t source, size_t dest);
        // Dijkstra's algorithm for finding the shortest paths in weighted graphs
        static std::vector<size_t> dijkstra(const Graph& g, size_t source, size_t dest);

        // Bellman-Ford algorithm for finding the shortest paths, can handle graphs with negative weights
        static std::vector<size_t> bellmanFord(const Graph& g, size_t source, size_t dest);

        // BFS for finding the shortest paths in unweighted graphs or checking graph connectivity
        static std::vector<size_t> bfs(const Graph& g, size_t source, size_t dest);

        // Helper method to construct the shortest path as a string
        static std::string constructPath(const std::vector<size_t>& path , size_t source,size_t dest);

        static int CalculatePathCost(std::vector<size_t> &path, const Graph &g);

        static std::vector<size_t> buildShortestPath (const Graph& g,  std::vector<int>& dist , size_t source ,size_t dest);

    };
}

#endif // SHORTEST_PATH_HPP