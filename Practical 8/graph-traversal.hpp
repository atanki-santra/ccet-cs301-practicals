#ifndef GRAPH_TRAVERSAL_HPP
#define GRAPH_TRAVERSAL_HPP

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>

using namespace std;

struct item
{
    char c;
    item* link;
};

struct charStack
{
    item* top{nullptr};
    void push(char ch)
    {
        if(!top)
        {
            top = new item();
            top->c = ch;
            return;
        }
        item* newItem = new item();
        newItem->link = top;
        newItem->c = ch;
        top = newItem;
    }
    char pop()
    {
        if(!top)
            return '\0';
        char popped = top->c;
        item* temp = top;
        top = top->link;
        delete temp;
        return popped;
    }
    char peek()
    {
        if(!top)
            return '\0';
        return top->c;
    }
    bool isEmpty()
    {
        if(top)
            return false;
        return true;
    }
};

struct charQueue
{
    item* front{nullptr};
    item* rear{nullptr};
    void push(char ch)
    {
        item* newItem = new item();
        newItem->c = ch;
        if(!front)
        {
            front = newItem;
            rear = newItem;
            front->link = nullptr;
            rear->link = nullptr;
            return;
        }
        rear->link = newItem;
        rear = rear->link;
    }
    char pop()
    {
        if(!rear)
            return '\0';
        char popped = front->c;
        item* temp = front;
        front = front->link;
        delete temp;
        return popped;
    }
    char peek()
    {
        if(!rear)
            return '\0';
        return front->c;
    }
    bool isEmpty()
    {
        if(front)
            return false;
        return true;
    }
};

struct edge
{
    char vertex;
    int weight;
};

struct node
{
    edge edg; 
    node* link;
};

struct edgeList
{
    node* start = nullptr;
    void add(char v, int w)
    {
        if(!start)
        {
            start = new node();
            start->edg.vertex = v;
            start->edg.weight = w;
            return;
        }
        node* newNode = new node();
        newNode->edg.vertex = v;
        newNode->edg.weight = w;
        node* current = start;
        while(current->link)
            current = current->link;
        current->link = newNode;
    }
};

edgeList* createGraph();
string depthFirstSearch(edgeList* graph);
string breadthFirstSearch(edgeList* graph);
void printAdjacencyList(edgeList* graph);

#endif //GRAPH_TRAVERSAL_HPP