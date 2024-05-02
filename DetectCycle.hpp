#ifndef DETECT_CYCLE_HPP
#define DETECT_CYCLE_HPP

#include "Graph.hpp"
#include <string>
#include <vector>


namespace ariel {
    class DetectCycle {
    public:
        static std::string Execute(const Graph &g);
    private:
        static std::string detectCycle(const Graph& g);
        static std::string constructCycleString(const std::vector<int> &cycle);
        static bool detectCycleDfs(const Graph &g, int v,int parent, std::vector<bool> &visited, std::vector<int> &path);
    };
}

#endif // DETECT_CYCLE_HPP
