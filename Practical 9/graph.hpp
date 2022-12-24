#ifndef GRAPH_TRAVERSAL_HPP
#define GRAPH_TRAVERSAL_HPP

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

struct item
{
    char c;
    item *link;
};

struct edge
{
    char vertex;
    int weight;
};

struct node
{
    edge edg;
    node *link;
};

struct edgeNode
{
    char v1;
    char v2;
    int weight;
    edgeNode *next{nullptr};
};

struct edgeList
{
    edgeNode *start{nullptr};
    void addEdgeNode(char first, char second, int wt)
    {
        edgeNode *newNode = new edgeNode();
        newNode->v1 = first;
        newNode->v2 = second;
        newNode->weight = wt;
        if (!start)
        {
            start = newNode;
            return;
        }
        if (start->weight > wt)
        {
            newNode->next = start;
            start = newNode;
            return;
        }
        if (!start->next)
        {
            start->next = newNode;
            return;
        }
        edgeNode *current = start->next;
        edgeNode *ptr = start;
        while (current->next)
        {
            if (current->weight > wt)
            {
                newNode->next = current;
                ptr->next = newNode;
                return;
            }
            current = current->next;
            ptr = ptr->next;
        }
        if (current->weight > wt)
        {
            newNode->next = current;
            ptr->next = newNode;
            return;
        }
        current->next = newNode;
    }
    edgeNode* pop()
    {
        if(!start)
            return nullptr;
        edgeNode* ptr = start;
        start = start->next;
        return ptr;
    }
    void printEdgList()
    {
        edgeNode *current = start;
        while (current)
        {
            cout << current->v1 << " <-> " << current->v2 << " : " << current->weight << endl;
            current = current->next;
        }
    }
};

struct list
{
    node *start = nullptr;
    void addNode(char v, int w)
    {
        node *newNode = new node();
        newNode->edg.vertex = v;
        newNode->edg.weight = w;
        newNode->link = nullptr;
        if (!start)
        {
            start = newNode;
            return;
        }
        node *current = start;
        while (current->link)
            current = current->link;
        current->link = newNode;
    }
    void removeNode(char v, int w)
    {
        if (!start)
            return;
        node *ptr = start;
        if (start->edg.vertex == v && start->edg.weight == w)
        {
            start = start->link;
            delete ptr;
            return;
        }
        node *current = start->link;
        while (current)
        {
            if (current->edg.vertex == v && current->edg.weight == w)
            {
                ptr->link = current->link;
                delete current;
                return;
            }
            current = current->link;
            ptr = ptr->link;
        }
        if (ptr->edg.vertex == v && ptr->edg.weight == w)
            delete ptr;
    }
    void clear()
    {
        node* ptr = start;
        node* current = start->link;
        while(current)
        {
            delete ptr;
            ptr = current;
            current = current->link;
        }
    }
};

list *createGraph();
void printAdjacencyList(list *graph);
edgeList *sortEdges(list *graph);
void kruskal(edgeList *edges);
void prims(char startVertex, list *graph);

#endif // GRAPH_TRAVERSAL_HPP