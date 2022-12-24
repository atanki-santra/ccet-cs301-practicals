#include "graph-traversal.hpp"

edgeList *createGraph()
{
    edgeList *vertexArray = new edgeList[7];
    vertexArray['a' - 97].add('b', 1);
    vertexArray['a' - 97].add('c', 4);
    vertexArray['b' - 97].add('a', 1);
    vertexArray['b' - 97].add('c', 2);
    vertexArray['b' - 97].add('d', 3);
    vertexArray['b' - 97].add('e', 10);
    vertexArray['c' - 97].add('a', 4);
    vertexArray['c' - 97].add('b', 2);
    vertexArray['c' - 97].add('d', 6);
    vertexArray['c' - 97].add('g', 3);
    vertexArray['d' - 97].add('b', 3);
    vertexArray['d' - 97].add('c', 6);
    vertexArray['d' - 97].add('e', 5);
    vertexArray['d' - 97].add('g', 1);
    vertexArray['e' - 97].add('b', 10);
    vertexArray['e' - 97].add('d', 5);
    vertexArray['e' - 97].add('g', 2);
    vertexArray['e' - 97].add('f', 7);
    vertexArray['f' - 97].add('e', 7);
    vertexArray['f' - 97].add('g', 5);
    vertexArray['g' - 97].add('f', 5);
    vertexArray['g' - 97].add('e', 2);
    vertexArray['g' - 97].add('d', 1);
    vertexArray['g' - 97].add('c', 3);
    return vertexArray;
}

void printAdjacencyList(edgeList* graph)
{
    char ch ='a';
    cout<<setw(10)<<left<<"Vertex "<<"   Adjacency List ({vertex , weigth})" <<endl;
    for(int i = 0; i<7;i++)
    {
        cout<<setw(10)<<left<<ch++ <<" : ";
        node* ptr = graph[i].start;
        while(ptr)
        {
            cout<<" {"<<ptr->edg.vertex<<','<<ptr->edg.weight<<"} ";
            ptr = ptr->link;
        }
        cout<<endl;
    }
}

string breadthFirstSearch(edgeList *graph)
{
    string path = "";
    bool marked[7];
    for (bool &m : marked)
        m = false;
    charQueue vQueue;
    vQueue.push('a');
    char vertex;
    while (!vQueue.isEmpty())
    {
        vertex = vQueue.pop();
        if (!marked[vertex - 97])
        {
            path.push_back(vertex);
            path = path + " -> ";
            marked[vertex - 97] = true;
            node *ptr = graph[vertex - 97].start;
            while (ptr)
            {
                if (!marked[(ptr->edg.vertex) - 97])
                    vQueue.push(ptr->edg.vertex);
                ptr = ptr->link;
            }
        }
    }
    path = path.substr(0, path.length() - 4);
    return path;
}

string depthFirstSearch(edgeList *graph)
{
    string path = "";
    bool marked[7];
    for (bool &m : marked)
        m = false;
    charStack vStack;
    vStack.push('a');
    char vertex;
    while (!vStack.isEmpty())
    {
        vertex = vStack.pop();
        if (!marked[vertex - 97])
        {
            path.push_back(vertex);
            path = path + " -> ";
            marked[vertex - 97] = true;
            node *ptr = graph[vertex - 97].start;
            while (ptr)
            {
                if (!marked[(ptr->edg.vertex) - 97])
                    vStack.push(ptr->edg.vertex);
                ptr = ptr->link;
            }
        }
    }
    path = path.substr(0, path.length() - 4);
    return path;
}