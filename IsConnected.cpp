#include <stdexcept>
#include "IsConnected.hpp"

namespace ariel {

    bool IsConnected::Execute(const ariel::Graph &g) {
        switch (g.getGraphType()) {
            case(GraphType::DIRECTED):
                return isConnectedDirected(g);

            case(GraphType::UNDIRECTED):
                return isConnectedUndirected(g);

            default:
                throw std::runtime_error("Unknown graph type encountered");
        }
    }

    bool IsConnected::isConnectedUndirected(const ariel::Graph &g) {
        // run dfs from an arbitrary vertex
        std::vector<bool> visited(g.getNumVertices(), false);
        dfs(g, visited, 0); // Start DFS from vertex 0

        // check if all the vertices were visited
        for(size_t v = 0; v < g.getNumVertices(); ++v)
            if(!visited[v])
                return false;
        return true;
    }

    bool IsConnected::isConnectedDirected(const ariel::Graph &g) {
        std::vector<bool> visited(g.getNumVertices(), false);

        for(size_t v = 0; v < g.getNumVertices(); ++v){
            if(!dfs(g, visited, v))
                return false;
        }
        return true;
    }

    bool IsConnected::dfs(const Graph &g, std::vector<bool>& visited, size_t start) {
        visited[start]=true;

        for(size_t v = 0; v < g.getNumVertices(); ++v){
            if(g.getEdgeWeight(start, v) != 0 && !visited[v])
                dfs(g, visited, v);
        }

        for(size_t v = 0; v < g.getNumVertices(); ++v)
            if(!visited[v])
                return false;
        return true;
    }
}
