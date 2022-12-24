#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <string>
using namespace std;

struct node
{
    string info{};
    node *leftChild{nullptr};
    node *rightChild{nullptr};
};

typedef struct node *BT;

struct item
{
    BT data;
    item *link;
};

struct nodeStack
{
    item *top = nullptr;
    void push(BT value)
    {
        item *new_item = new item();
        new_item->data = value;
        new_item->link = top;
        top = new_item;
    }
    BT pop()
    {
        BT rvalue = top->data;
        item *temp_ptr = top;
        top = top->link;
        delete temp_ptr;
        return rvalue;
    }
    BT peek()
    {
        return top->data;
    }
    bool isEmpty()
    {
        if (top)
            return false;
        return true;
    }
};

struct intStack
{
    int top = -1;
    size_t SIZE = 0;
    int *array;
    void create(size_t size)
    {
        SIZE = size;
        array = new int[size];
        top = 0;
    }
    void push(int value)
    {
        if (top == SIZE)
        {
            cout << "Overflow Condition!" << endl;
            exit(1);
        }
        top++;
        array[top] = value;
    }
    int pop()
    {
        if (top < 0)
        {
            cout << "Underflow Condition!" << endl;
            exit(1);
        }
        double rvalue = array[top];
        top--;
        return rvalue;
    }
    int peek()
    {
        if (isEmpty())
        {
            cout << "Underflow Condition!" << endl;
            exit(1);
        }
        return array[top];
    }
    size_t isEmpty()
    {
        if (top == -1)
            return true;
        return false;
    }
};

#endif // STRUCTURE_H