#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "GraphProperties.hpp"
#include <cstddef>
namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        size_t numVertices;
        size_t numEdges;
        GraphType graphType;
        EdgeType edgeType;
        EdgeNegativity edgeNegativity;

        void clearGraph() ;
        [[nodiscard]] static bool isValidGraph(const std::vector<std::vector<int>>& adjacencyMatrix) ;
        [[nodiscard]] static bool isSymmetricMatrix(const std::vector<std::vector<int>>& matrix) ;

    public:
        Graph();

        // graph methods
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        bool isEmpty() const;

        // getters
        [[nodiscard]] size_t V() const;
        [[nodiscard]] GraphType getGraphType() const;
        [[nodiscard]] EdgeType getEdgeType() const;
        [[nodiscard]] EdgeNegativity getEdgeNegativity() const;
        [[nodiscard]] int getEdgeWeight(size_t u, size_t v) const;
        [[nodiscard]] std::vector<size_t> getNeighbors(size_t vertex) const;
        [[nodiscard]] Graph getReversedGraph() const;


    };
}

#endif // GRAPH_HPP