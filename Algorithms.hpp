#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "DetectCycle.hpp"
#include "IsBipartite.hpp"
#include "IsConnected.hpp"
#include "DetectNegativeCycle.hpp"
#include <string>

namespace ariel {
    class Algorithms {
    public:
        static bool isConnected(const Graph& g);
        static std::string shortestPath(const Graph& g, size_t start, size_t end);
        static std::string isContainsCycle(const Graph& g);
        static std::string negativeCycle(const Graph& g);
        static std::string isBipartite(const Graph& g);

    };
}
#endif // ALGORITHMS_HPP