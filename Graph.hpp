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

        bool isValidGraph(const std::vector<std::vector<int>>& adjacencyMatrix) const;
        bool isSymmetricMatrix(const std::vector<std::vector<int>>& matrix) const;

    public:
        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        [[nodiscard]] bool isDirectedGraph() const;
        [[nodiscard]] size_t getNumVertices() const;
        [[nodiscard]] std::vector<std::vector<int>> getAdjacencyMatrix() const;
        [[nodiscard]] GraphType getGraphType() const;
        [[nodiscard]] EdgeType getEdgeType() const;
        [[nodiscard]] EdgeNegativity getEdgeNegativity() const;
        [[nodiscard]] int getEdgeWeight(size_t u, size_t v) const;
        [[nodiscard]] std::vector<size_t> getNeighbors(size_t vertex) const;

    private:
        void clearGraph() ;

    };
}

#endif // GRAPH_HPP