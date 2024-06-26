//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#include "Graph.hpp"
namespace ariel {

    /**
    * Constructs an empty graph with default attributes.
    */
    Graph::Graph() : numVertices(0), numEdges(0), graphType(GraphType::UNDIRECTED),
                     edgeType(EdgeType::UNWEIGHTED), edgeNegativity(EdgeNegativity::NONE) {}
    /**
    * Loads a graph from an adjacency matrix, setting properties such as number of vertices, number of edges,
    * graph type, edge type, and edge negativity based on the loaded data.
    * @param matrix The adjacency matrix representing the graph.
    * @throws std::invalid_argument if the matrix is not square.
     */
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

    /**
     * Clears the graph data, resetting it to an empty state.
     */
    void Graph::clearGraph() {
        this->numVertices = 0;
        this->numEdges = 0;
        this->adjacencyMatrix.clear();
        this->graphType = GraphType::UNDIRECTED;
        this->edgeType = EdgeType::UNWEIGHTED;
        this->edgeNegativity = EdgeNegativity::NONE;
    }

    bool Graph::isValidGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
        for(const auto& row : adjacencyMatrix) {
            if (row.size() != adjacencyMatrix.size()) {
                return false;
            }
        }
        return true;
    }

    bool Graph::isSymmetricMatrix(const std::vector<std::vector<int>>& matrix) {
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

    void Graph::printGraph() const {
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
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

    size_t Graph::V() const {
        return numVertices;
    }

    int Graph::getEdgeWeight(size_t u, size_t v) const {
        return adjacencyMatrix[u][v];
    }

    Graph Graph::getReversedGraph() const {
        // Create a new graph
        Graph reversedGraph;

        // Reverse the adjacency matrix
        std::vector<std::vector<int>> reversedAdjacencyMatrix(numVertices, std::vector<int>(numVertices, 0));

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    reversedAdjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                }
            }
        }

        // Load the reversed adjacency matrix into the reversed graph
        reversedGraph.loadGraph(reversedAdjacencyMatrix);

        return reversedGraph;
    }

    /**
     * @brief Adds a new vertex to the graph with outgoing edges to existing vertices.
     *
     * This method creates a new graph with an additional vertex compared to the original graph.
     * Outgoing edges are added from the new vertex to each existing vertex in the original graph.
     *
     * @return A new graph with the added vertex and outgoing edges.
       */
    Graph Graph::addVertexWithEdges() const {
        // Create a new graph
        Graph modifiedGraph;

        // Increase the size of the adjacency matrix to accommodate the new vertex
        size_t newSize = numVertices + 1;
        std::vector<std::vector<int>> modifiedAdjacencyMatrix(newSize, std::vector<int>(newSize, 0));

        // Copy existing adjacency matrix to modified adjacency matrix
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                modifiedAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
            }
        }

        // assign max value possible for each new outgoing edge
        int outgoingEdgeWeight = 10000;

        // For directed graphs, add outgoing edges from the new vertex to each existing vertex
        for (size_t i = 0; i < numVertices; ++i) {
            modifiedAdjacencyMatrix[newSize - 1][i] = outgoingEdgeWeight;
        }


        // Set the weight of the self-loop of the new vertex to 0
        modifiedAdjacencyMatrix[newSize - 1][newSize - 1] = 0;

        // Load the modified adjacency matrix into the modified graph
        modifiedGraph.loadGraph(modifiedAdjacencyMatrix);

        return modifiedGraph;
    }


    bool Graph::isEmpty() const {
        return numVertices<=0;
    }
} // namespace ariel