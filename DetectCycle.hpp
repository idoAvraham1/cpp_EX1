#ifndef DETECT_CYCLE_HPP
#define DETECT_CYCLE_HPP

#include "Graph.hpp"
#include <string>
#include <vector>

namespace ariel {
    class DetectCycle {
    public:
        static std::string Execute(const Graph& g);

    private:
        static std::string detectCycleWithNegativeEdges(const Graph& g);
        static std::string detectCycleNoNegativeEdges(const Graph& g);
    };
}

#endif // DETECT_CYCLE_HPP
