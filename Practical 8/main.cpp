#include <iostream>
#include "graph-traversal.hpp"
using namespace std;

int main()
{
     edgeList *graph = createGraph();
     printAdjacencyList(graph);
     string result = depthFirstSearch(graph);
     cout << endl
          << "The DFS Traversal of the graph is :" << endl
          << result << endl;
     result = breadthFirstSearch(graph);
     cout << "The BFS Traversal of the graph is :" << endl
          << result << endl;
     return 0;
}