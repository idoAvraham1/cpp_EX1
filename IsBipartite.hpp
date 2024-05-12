//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#ifndef IS_BIPARTITE_HPP
#define IS_BIPARTITE_HPP

#include "Graph.hpp"
#include "IsConnected.hpp"
#include <string>
#include <vector>
#include <unordered_set>


namespace ariel {
    class IsBipartite {
    public:
        static std::string Execute(const ariel::Graph &g);

    private:
        static bool  colorGraphBFS(const Graph& g, std::vector<int>& colors, size_t start);
        static std::string FindPartition(std::vector<int>& colors);
    };
}

#endif // IS_BIPARTITE_HPP
