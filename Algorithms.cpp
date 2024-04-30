#include "Algorithms.hpp"


#include <stdexcept>

#include "GraphProperties.hpp"


namespace ariel {

    std::string Algorithms::shortestPath(const Graph& g, size_t start, size_t end) {
        return ShortestPath::Execute(g, start, end);
    }

    bool Algorithms::isConnected(const Graph& g) {
        return IsConnected::Execute(g);
    }

    std::string Algorithms::isContainsCycle(const Graph &g) {
        return DetectCycle::Execute(g);
    }

    std::string Algorithms::negativeCycle(const Graph &g) {
        return DetectCycle::Execute(g);
    }


    std::string Algorithms::isBipartite(const Graph &g) {
        return IsBipartite::Execute(g);
    }


}