#include "Graph.hpp"

#include <iostream>
#include <stdexcept>

namespace ariel {

    Graph::Graph() : numVertices(0), numEdges(0), graphType(GraphType::UNDIRECTED),
                     edgeType(EdgeType::UNWEIGHTED), edgeNegativity(EdgeNegativity::NONE) {}

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        if (!isValidGraph(matrix)) {
            throw std::invalid_argument("Invalid graph: Graph is not valid.");
        }

        clearGraph();


        this->numVertices = matrix.size();
        this->adjacencyMatrix = matrix;
        this->numEdges = 0;

        // Count edges and check for weighted and negative edges
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    this->numEdges++;
                    if (adjacencyMatrix[i][j] != 1) {
                        this->edgeType = EdgeType::WEIGHTED;
                        if (adjacencyMatrix[i][j] < 0) {
                            this->edgeNegativity = EdgeNegativity::NEGATIVE;
                        }
                    }
                }
            }
        }

        // Check if graph is directed
        if (!isSymmetricMatrix(matrix)) {
            this->graphType = GraphType::DIRECTED;
        }
    }
    void Graph::clearGraph() {
        this->numVertices = 0;
        this->numEdges = 0;
        this->adjacencyMatrix.clear();
        this->graphType = GraphType::UNDIRECTED;
        this->edgeType = EdgeType::UNWEIGHTED;
        this->edgeNegativity = EdgeNegativity::NONE;
    }

    bool Graph::isValidGraph(const std::vector<std::vector<int>>& adjacencyMatrix) const {
        for(const auto& row : adjacencyMatrix) {
            if (row.size() != adjacencyMatrix.size()) {
                return false;
            }
        }
        return true;
    }

    bool Graph::isSymmetricMatrix(const std::vector<std::vector<int>>& matrix) const {
        size_t n = matrix.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }
    std::vector<size_t> Graph::getNeighbors(size_t vertex) const {
        std::vector<size_t> neighbors;

        // Check the corresponding row or column in the adjacency matrix
        for (size_t i = 0; i < numVertices; ++i) {
            if (adjacencyMatrix[vertex][i] != 0) {
                // If there is a non-zero edge weight, add the vertex to the neighbors list
                neighbors.push_back(i);
            }
        }

        return neighbors;
    }

    void Graph::printGraph() const {
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
    }

    bool Graph::isDirectedGraph() const {
        return (graphType == GraphType::DIRECTED);
    }

    GraphType Graph::getGraphType() const {
        return graphType;
    }

    EdgeType Graph::getEdgeType() const {
        return edgeType;
    }

    EdgeNegativity Graph::getEdgeNegativity() const {
        return edgeNegativity;
    }

    size_t Graph::getNumVertices() const {
        return numVertices;
    }

    std::vector<std::vector<int>> Graph::getAdjacencyMatrix() const {
        return adjacencyMatrix;
    }

    int Graph::getEdgeWeight(size_t u, size_t v) const {
        return adjacencyMatrix[u][v];
    }

} // namespace ariel