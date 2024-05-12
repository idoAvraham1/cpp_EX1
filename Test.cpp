//written by ido avraham : 208699181
//EMAIL: idoavraham086@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
using namespace std;




TEST_CASE("Test isConnected")
{
    ariel::Graph g;

    // undirected graphs
    {
        // connected graph
        vector<vector<int>> graph1 = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph1);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> graph2 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

    // directed graphs
    {
        // disconnected graphs
        vector<vector<int>> graph3 = {
                {0, 1, 0},
                {0, 0, 1},
                {0, 0, 0}};
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isConnected(g) == false);

        vector<vector<int>> graph4 = {
                {0, 1, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0},
                {1, 0, 0, 0, 1},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isConnected(g) == false);

        // connected graph - strongly connected directed graph
        vector<vector<int>> graph5 = {
                {0, 1, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0},
                {1, 0, 0, 0, 1},
                {0, 0, 0, 2, 0}
        };
        g.loadGraph(graph5);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> graph6 = {
                {0, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1},
                {1, 0, 0, 0},

        };
        g.loadGraph(graph6);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

}


TEST_CASE("Test shortestPath")
{
    ariel::Graph g;

    // BFS cases
    {
        // Test shortest path with unweighted undirected graph (BFS)
        vector<vector<int>> graph1 = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}
        };
        g.loadGraph(graph1);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Shortest path from 0 to 2 is: 0->1->2");

        vector<vector<int>> graph2 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "Shortest path from 0 to 3 is: 0->2->3");

        // Test shortest path with unweighted undirected graph with no path (BFS)
        vector<vector<int>> graph3 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "There is no path from 0 to 4");

        // Test shortest path with unweighted directed graph (BFS)
        vector<vector<int>> graph4 = {
                {0, 1, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "Shortest path from 0 to 4 is: 0->1->2->3->4");

        // Test shortest path with unweighted directed graph with no path (BFS)
        vector<vector<int>> graph5 = {
                {0, 1, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph5);
        CHECK(ariel::Algorithms::shortestPath(g, 4, 0) == "There is no path from 4 to 0");
    }

    // BELLMAN-FORD CASES
    {
        // Test the shortest path with negative weights without a negative cycle, undirected graph (Bellman-Ford)
        vector<vector<int>> graph6 = {
                {0,  -1, 3},
                {-1, 0,  1},
                {3,  1,  0}
        };
        g.loadGraph(graph6);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Shortest path from 2 to 0 is: 0->1->2");

        // Test the shortest path with negative weights without a negative cycle, undirected graph (Bellman-Ford)
        vector<vector<int>> graph18= {
                {  0, -1, 0, 10,} ,
                {-1, 0, 0, 10,},
                { 0, 0, 0, 10,},
                { 10, 10, 10, 0,},
        };
        g.loadGraph(graph18);
        CHECK( ariel::Algorithms::shortestPath(g,0,3)== "Shortest path from 0 to 3 is: 0->1->3" );

        // Test the shortest path with negative weights without a negative cycle, undirected graph (Bellman-Ford)
        vector<vector<int>> graph19={
                {0, -1, 0, 10, 10, 10,},
                { -1, 0, 0, 10, 0, 0,},
                { 0, 0, 0, 10, 0, 0,},
                { 10, 10, 10, 0, 0, 0,},
                { 10, 0, 0, 0, 0, -1,},
                { 10, 0, 0, 0, -1, 0,},
        };
        g.loadGraph(graph19);
        CHECK( ariel::Algorithms::shortestPath(g,3,4)== "Shortest path from 4 to 3 is: 3->1->0->5->4" );


        // Test shortest path with negative weight, negative cycle in the graph,directed, disconnected graph (Bellman-Ford)
        vector<vector<int>> graph7 = {
                {0, 1, 0,  0, 0},
                {0, 0, -5, 0, 0},
                {2, 0, 0,  0, 0},
                {0, 0, 0,  0, 2},
                {0, 0, 0,  0, 0}
        };
        g.loadGraph(graph7);

        //Negative cycle detected in the graph
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 2));

        // find the shortest path in directed graph with negative cycle but 2 CC
        CHECK(ariel::Algorithms::shortestPath(g, 3, 4) == "Shortest path from 3 to 4 is: 3->4");

        // Test shortest path with negative weights without negative cycle, directed graph (Bellman-Ford)
        vector<vector<int>> graph8 = {
                {0, 1, 2, 0, 0},
                {0, 0, -5, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 2},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph8);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Shortest path from 0 to 2 is: 0->1->2");
    }

    // DIJKSTRA CASES
    {
        // Test shortest path with weighted graph, positive weights directed graph
        vector<vector<int>> graph8 = {
                {0, 9, 0, 2, 0},
                {9, 0, 3, 0, 0},
                {0, 3, 0, 0, 1},
                {2, 0, 0, 0, 2},
                {0, 0, 1, 2, 0}
        };
        g.loadGraph(graph8);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "Shortest path from 0 to 1 is: 0->3->4->2->1");

        // Test shortest path with weighted graph, positive weights no path directed graph
        vector<vector<int>> graph9 = {
                {0, 9, 0, 2, 0},
                {9, 0, 3, 0, 0},
                {0, 3, 0, 0, 0},
                {2, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph9);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "There is no path from 0 to 4");

        // Test shortest path with weighted graph, positive weights undirected graph
        vector<vector<int>> graph10 = {
                {0, 9, 0, 2, 0},
                {9, 0, 3, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 3},
                {0, 2, 0, 0, 0}
        };
        g.loadGraph(graph10);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "Shortest path from 0 to 1 is: 0->3->4->1");


        // Test shortest path with weighted graph, positive weights no path undirected graph
        vector<vector<int>> graph11 = {
                {0, 0, 0, 2, 0},
                {9, 0, 3, 1, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 3},
                {1, 0, 4, 0, 0}
        };
        g.loadGraph(graph11);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "There is no path from 0 to 1");

        vector<vector<int>> graph12 = {
                {0, 1, 0, 12 },
                {1, 0, 0, 10},
                {0, 0, 0, 10},
                {12, 10, 10, 0}
        };
        g.loadGraph(graph12);
        CHECK(ariel::Algorithms::shortestPath(g, 3, 0) == "Shortest path from 3 to 0 is: 3->1->0");
    }
}

TEST_CASE("Test NegativeCycle")
{
    ariel::Graph g;
    //directed graph

    // negative cycle directed graph
    vector<vector<int>> graph1 = {
                {0, 1, 0,  0, 0},
                {0, 0, -5, 0, 0},
                {2, 0, 0,  0, 0},
                {0, 0, 0,  0, 2},
                {0, 0, 0,  0, 0}
        };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 0 -> 1 -> 2 -> 0");

    // negative cycle in directed graph
    vector<vector<int>> graph4 = {
            {0,1,-2,4},
            {1, 0, -1,0},
            {0, -1, 0,0},
            {0, 0, 2 , 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1 -> 2 -> 1");

    // negative cycle in directed graph
    vector<vector<int>> graph9 = {
            {0,1,0,4},
            {1, 0, -1,0},
            {-2, 0, 0,0},
            {0, 0, 2 , 0}
    };
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 0 -> 1 -> 2 -> 0");


    // negative cycle in undirected graph
    vector<vector<int>> graph2 = {
            {0, 1, 2, 0, 0},
            {1, 0, -5, 0, 0},
            {2, -5, 0, 0, 0},
            {0, 0, 0, 0, 2},
            {0, 0, 0, 2, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) =="Negative cycle found: 0 -> 1 -> 2 -> 0");

    // negative cycle in undirected graph
    vector<vector<int>> graph= {
            {0, -1, 3,},
            {-1, 0, -3,},
            {3, -3, 0,},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 0 -> 1 -> 2 -> 0");

    // negative cycle in undirected graph
    vector<vector<int>> graph18= {
            {  0, -1, 0, -10,} ,
            {-1, 0, 0, 10,},
            { 0, 0, 0, 10,},
            { -10, 10, 10, 0,},
    };
    g.loadGraph(graph18);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 0 -> 3 -> 1 -> 0");

    // negative cycle in undirected graph
    vector<vector<int>> graph3 = {
            {0, 1, 2, 0, 0},
            {1, 0, 5, 0, 1},
            {2, 5, 0, 0, 0},
            {0,-4, 0, 0, 0},
            {0, 1, 0, 2, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 3 -> 1 -> 4 -> 3");



    // no negative cycle directed graphs
    vector<vector<int>> graph5 = {
            {0, 0, 3},
            {-1, 0, 1},
            {0, 1, 0}
    };
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in the graph" );

    // no negative cycle in directed graph
    vector<vector<int>> graph8 = {
            {0, 1, 2, 0, 0},
            {0, 0, -5, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2},
            {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in the graph" );

    // no negative cycle in undirected graph
    vector<vector<int>> graph41 = {
            {0, 1, 10 },
            {1, 0, -5 },
            {10, -5, 0},
    };
    g.loadGraph(graph41);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in the graph" );

    // no negative cycle in undirected graph
    vector<vector<int>> graph42 = {
            {0, 1, 10, 0, 0},
            {1, 0, -5, 0, 0},
            {10, -5, 0, 0, 0},
            {0, 0, 0, 0, 2},
            {0, 0, 0, 2, 0}
    };
    g.loadGraph(graph41);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in the graph" );
}


TEST_CASE("Test isContainsCycle")
{    ariel::Graph g;
    //  undirected graphs
    {
        // no cycle

        vector<vector<int>> graph1 = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}};
        g.loadGraph(graph1);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
        // cycle
        vector<vector<int>> graph2 = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "Cycle found: 0->1->2->0");
    }


    // directed graph
    {
        // cycle
        vector<vector<int>> graph3 = {
                {0, 1, 0,  0, 0},
                {0, 0, -5, 0, 0},
                {2, 0, 0,  0, 0},
                {0, 0, 0,  0, 2},
                {0, 0, 0,  0, 0}
        };
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "Cycle found: 0->1->2->0");

        // no cycle
        vector<vector<int>> graph4 = {
                {0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {2, 0, 0, 0, 0},
                {0, 0, 0, 0, 2},
                {0, 0, 0, 0, 0}
        };
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");
    }
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;

    // bipartite graphs
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is bipartite, A={0,2}, B={1}");

    vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is bipartite, A={0,2,4}, B={1,3}");

    vector<vector<int>> bipartite_graph = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {1, 0, 1, 0}
    };
    g.loadGraph(bipartite_graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is bipartite, A={0,2}, B={1,3}");

    vector<vector<int>> graph6 = {
            {0, 1, 1, 0},
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {0, 1, 1, 0},
    };
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is bipartite, A={0,3}, B={1,2}");


    // un bipartite graphs
    vector<vector<int>> graph4 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not bipartite");

    // Non-Bipartite graph
    vector<vector<int>> non_bipartite_graph = {
            {0, 1, 1, 0},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {0, 1, 1, 0}
    };
    g.loadGraph(non_bipartite_graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not bipartite");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    CHECK(ariel::Algorithms::isBipartite(g) =="Graph is empty");

    vector<vector<int>> graph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {
            {0,  -1, 3},
            {-1, 0,  1},
            {3,  1,  0}
    };
    g.loadGraph(graph2);
    CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 5));



}
