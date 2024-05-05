#ifndef DETECT_CYCLE_HPP
#define DETECT_CYCLE_HPP

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include <string>
#include <vector>


namespace ariel {
    class DetectCycle {
    public:
        static std::string Execute(const Graph &g, bool onlyNegativeCycle);
    private:
        static std::string detectCycle(const Graph& g);
        static std::string constructCycleString(const std::vector<int> &cycle);
        static bool detectCycleDfs(const Graph &g, int v,int parent, std::vector<bool> &visited, std::vector<int> &path);
        static std::string detectNegativeCycle(const Graph& g);
    };

}

#endif // DETECT_CYCLE_HPP
