/*Problem 9: Minimum Spanning Tree (MST): Consider the connected graph with non-negative weights on
the edges shown in Figure 1 and apply the following algorithms to find a spanning tree T for which the
sum of the weights on the edges in T is as small as possible.
 Kruskal’s Algorithm
 Prim’s Algorithm*/

#include <iostream>
#include <string>
#include "graph.hpp"
using namespace std;

int main()
{
    list *graph{nullptr};
    cout << string(70, '-') << endl
         << "GIVEN GRAPH :" << endl
         << string(70, '-') << endl;
    graph = createGraph();
    printAdjacencyList(graph);
    edgeList *edges = sortEdges(graph);
    cout << string(70, '-') << endl
         << "SORTED EDGES :" << endl
         << string(70, '-') << endl;
    edges->printEdgList();
    cout << string(70, '-') << endl
         << "MINIMUM SPANNING TREE GENERATED :" << endl
         << string(70, '-') << endl;
    kruskal(edges);
    graph->clear();
    cout << string(70, '-') << endl
         << "PRIM'S ALGORITHM" << endl
         << string(70, '-') << endl
         << "ENTER THE STARTING VERTEX :" << endl;
    char vertex;
    cin >> vertex;
    cout << string(70, '-') << endl
         << "MINIMUM SPANNING TREE GENERATED :" << endl
         << string(70, '-') << endl;
    graph = createGraph();
    prims(vertex, graph);
    graph->clear();
    cout << string(70, '-') << endl;
    return 0;
}