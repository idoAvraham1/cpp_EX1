
**Project Purpose:**
The purpose of this project is to implement various graph algorithms using an adjacency matrix representation. The algorithms included in this project are:

  * *isContainCycle:*  Checks if a given graph contains any cycle.

  * *Shortest Path:* Finds the shortest path from a given source vertex to a destination vertex.

  * *negativeCycle*: Checks if a given graph contains only negative cycles.

  * *isConnected:* Determines if a given graph is connected.

  * *isBipartite:* Checks if a given graph can be bipartite.

  These algorithms serve various purposes such as pathfinding, cycle detection, and connectivity analysis in graph data structures.


**Graph Representation and Properties:**
The graph is represented using an adjacency matrix, where an entry [i][j] represents the weight of the edge between vertex i and vertex j. A weight of zero indicates the absence of an edge.
Three main properties of the graph are determined from the adjacency matrix:

  * *GraphType:* Directed or Undirected. An undirected graph has a symmetric adjacency matrix.

  * *EdgeType:* Weighted or Unweighted. If all entries in the adjacency matrix have a weight of 1, the graph is considered unweighted.

  * *EdgeNegativity:* Negative or None. If at least one entry in the adjacency matrix has a weight > 0, then the graph has negativity; otherwise, it has none.


**Project Structure:**
The project consists of seven main classes and one header file for graph properties enumeration. These classes are:

   * *Graph*: Represents a graph with an adjacency matrix.

  * *Algorithms*: Provides a class for invoking each desired algorithm.

  * *GraphProperties*: Header file defining enums for graph properties.

  Additionally, there is a class for each algorithm: ShortestPath, DetectNegativeCycle, isContainsCycle, isBipartite, and isConnected.
  The decision to divide the Algorithms class into separate classes for each algorithm was made to adhere to Object-Oriented Programming (OOP) principles. Each class has a single responsibility, promoting code modularity and adhering to the Open-Closed principle. This design allows for easy extension by adding new algorithm classes without modifying existing code.


**Detailed Description of Algorithms:**
Each concrete algorithm class provides a public method called execute, responsible for executing the algorithm according to the graph properties and checking for valid input. Here's a brief overview of each algorithm:

  * *ShortestPath*: Finds the path from a source vertex to a destination vertex using Dijkstra's algorithm for non-negative weighted graphs, BFS for unweighted graphs, and Bellman-Ford for graphs with negative weights.

  * *isBipartite*: Determines if a graph can be bipartite and, if so, finds the actual partitions of the set of vertices into two disjoint sets.

  * isContainsCycle:** Determines if a graph contains any cycle, regardless of negativity. Ignores cycles with only one edge in undirected graphs.

  * *isConnected:* Determines if a graph is connected, considering strongly connected graphs for directed graphs.

  * *DetectNegativeCycle:* Identifies negative cycles in the graph using Bellman-Ford's logic.

