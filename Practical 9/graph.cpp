#include "graph.hpp"

list *createGraph()
{
    list *graph = new list[8];
    graph['1' - 49].addNode('6', 54);
    graph['1' - 49].addNode('3', 47);
    graph['1' - 49].addNode('5', 80);
    graph['3' - 49].addNode('1', 47);
    graph['3' - 49].addNode('6', 75);
    graph['3' - 49].addNode('5', 23);
    graph['3' - 49].addNode('4', 88);
    graph['3' - 49].addNode('2', 55);
    graph['3' - 49].addNode('7', 66);
    graph['6' - 49].addNode('1', 54);
    graph['6' - 49].addNode('3', 75);
    graph['6' - 49].addNode('4', 74);
    graph['5' - 49].addNode('1', 80);
    graph['5' - 49].addNode('3', 23);
    graph['5' - 49].addNode('2', 32);
    graph['5' - 49].addNode('7', 93);
    graph['7' - 49].addNode('5', 93);
    graph['7' - 49].addNode('3', 66);
    graph['7' - 49].addNode('2', 74);
    graph['7' - 49].addNode('8', 68);
    graph['2' - 49].addNode('3', 55);
    graph['2' - 49].addNode('4', 31);
    graph['2' - 49].addNode('8', 79);
    graph['2' - 49].addNode('7', 74);
    graph['2' - 49].addNode('5', 32);
    graph['8' - 49].addNode('2', 79);
    graph['8' - 49].addNode('7', 68);
    graph['8' - 49].addNode('4', 29);
    graph['4' - 49].addNode('6', 74);
    graph['4' - 49].addNode('3', 88);
    graph['4' - 49].addNode('2', 31);
    graph['4' - 49].addNode('8', 29);
    return graph;
}

void printAdjacencyList(list *graph)
{
    char ch = '1';
    cout << setw(10) << left << "Vertex "
         << "   Adjacency List ({vertex , weigth})" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << setw(10) << left << ch++ << " : ";
        node *ptr = graph[i].start;
        while (ptr)
        {
            cout << " {" << ptr->edg.vertex << ',' << ptr->edg.weight << "} ";
            ptr = ptr->link;
        }
        cout << endl;
    }
}

edgeList *sortEdges(list *graph)
{
    edgeList *edges = new edgeList();
    for (int i = 0; i < 8; i++)
    {
        node *ptr = graph[i].start;
        while (ptr)
        {
            edges->addEdgeNode(i + 49, ptr->edg.vertex, ptr->edg.weight);
            graph[ptr->edg.vertex - 49].removeNode(i + 49, ptr->edg.weight);
            ptr = ptr->link;
        }
    }
    return edges;
}

int find(int i, int *parent)
{
    if (parent[i] == -1)
        return i;

    return parent[i] = find(parent[i], parent);
}

void unite(int x, int y, int *parent, int *rank)
{
    int s1 = find(x, parent);
    int s2 = find(y, parent);

    if (s1 != s2)
    {
        if (rank[s1] < rank[s2])
        {
            parent[s1] = s2;
            rank[s2] += rank[s1];
        }
        else
        {
            parent[s2] = s1;
            rank[s1] += rank[s2];
        }
    }
}

void kruskal(edgeList *edges)
{
    int total_cost{0};
    edgeNode *ptr = edges->start;
    int *parent = new int[8];
    for (int i = 0; i <= 8; i++)
        parent[i] = -1;
    int *rank = new int[8];
    for (int i = 0; i <= 8; i++)
        rank[i] = 1;
    while (ptr)
    {
        if (find(ptr->v1 - 49, parent) != find(ptr->v2 - 49, parent))
        {
            unite(ptr->v1 - 49, ptr->v2 - 49, parent, rank);
            total_cost += ptr->weight;
            cout << ptr->v1 << " -- " << ptr->v2 << " == " << ptr->weight
                 << endl;
        }
        ptr = ptr->next;
    }
    cout << "Total Cost : " << total_cost << endl;
}

void prims(char startVertex, list *graph)
{
    edgeList edges;
    edgeNode *minEdge{nullptr};
    int total_cost{0};
    int *parent = new int[8];
    for (int i = 0; i <= 8; i++)
        parent[i] = -1;
    int *rank = new int[8];
    for (int i = 0; i <= 8; i++)
        rank[i] = 1;
    int vertex = startVertex - 49;
    node *ptr{nullptr};
    edges.addEdgeNode('\0', '\0', INT16_MAX);
    while (edges.start)
    {
        ptr = graph[vertex].start;
        while (ptr)
        {
            edges.addEdgeNode(vertex + 49, ptr->edg.vertex, ptr->edg.weight);
            graph[ptr->edg.vertex - 49].removeNode(vertex + 49, ptr->edg.weight);
            ptr = ptr->link;
        }
        while (true)
        {
            minEdge = edges.pop();
            if (minEdge->v1 == '\0')
            {
                delete minEdge;
                break;
            }
            if (find(minEdge->v1 - 49, parent) != find(minEdge->v2 - 49, parent))
            {
                unite(minEdge->v1 - 49, minEdge->v2 - 49, parent, rank);
                total_cost += minEdge->weight;
                cout << minEdge->v1 << " -- " << minEdge->v2 << " == " << minEdge->weight
                     << endl;
                vertex = minEdge->v2 - 49;
                delete minEdge;
                break;
            }
        }
    }
    cout << "Total Cost : " << total_cost << endl;
}