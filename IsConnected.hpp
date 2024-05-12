//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#ifndef IS_CONNECTED_HPP
#define IS_CONNECTED_HPP

#include "DetectCycle.hpp"
#include "Graph.hpp"
using namespace std;

namespace ariel {
    class IsConnected {
    public:
            static bool Execute(const ariel::Graph &g);
    private:
        static bool isConnectedDirected(const Graph& g);
        static bool isConnectedUndirected(const Graph& g);
        static void dfs(const Graph& g, std::vector<bool>& visited , size_t start);

    };
}

#endif // IS_CONNECTED_HPP
