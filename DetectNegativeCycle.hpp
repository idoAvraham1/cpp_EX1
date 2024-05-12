//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com

#ifndef CPP_EX1_DETECTNEGATIVECYCLE_HPP
#define CPP_EX1_DETECTNEGATIVECYCLE_HPP

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include <string>
#include <vector>

namespace ariel {
    class DetectNegativeCycle {
    public:
        static std::string Execute(const Graph &g);

    private:
        static std::string detectNegativeCycle(const Graph &g);
        static std::string bellmanFord(const Graph& g, size_t source);
        static std::string findNegativeCycle(const Graph &g,  std::vector<int> &dist, std::vector<size_t> &predecessors);
    };
}


#endif //CPP_EX1_DETECTNEGATIVECYCLE_HPP
