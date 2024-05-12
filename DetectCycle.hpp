//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#ifndef DETECT_CYCLE_HPP
#define DETECT_CYCLE_HPP

#include "Graph.hpp"
#include "ShortestPath.hpp"
using namespace std;


namespace ariel {
    class DetectCycle {
    public:
        static std::string Execute(const Graph &g);
    private:
        static std::string detectCycle(const Graph& g);
        static bool detectCycleDfs(const Graph &g, size_t v,int parent, std::vector<bool> &visited, std::vector<size_t> &path);
        static std::string constructCycleString(const std::vector<size_t> &path);
    };

}

#endif // DETECT_CYCLE_HPP
