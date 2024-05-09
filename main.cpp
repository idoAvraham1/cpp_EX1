/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

/**
 * example to a  unDirected graph that bellman ford fails to find shortest path from 3 to 0 OR 3 to 1
      -1, 0, 0, 10,
       0, 0, 0, 10,
       10, 10, 10, 0,
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/*
int main()
{
    ariel::Graph g;
    vector<vector<int>> graph6 = {
            {0,1, 2,4},
            {1, 0, -1,0},
            {0,-1, 0,0},
            {0, 0,2, 0}
    };
    g.loadGraph(graph6);
   cout<<Algorithms::shortestPath(g,0,3) <<endl;
   cout<<Algorithms::negativeCycle(g)<<endl;

    vector<vector<int>> graph3 = {
            {0, 0, 2, 0, 0},
            {0, 0, 5, 0, 1},
            {0, 5, 0, 0, 0},
            {0,-4, 0, 0, 0},
            {0, 1, 0, 2, 0}
    };
    g.loadGraph(graph3);
    cout<<Algorithms::negativeCycle(g)<<endl;


}
*/




