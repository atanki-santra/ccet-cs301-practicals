#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>
using namespace std;

struct item
{
    string data;
    item *link;
};

struct stack
{
    item *top = nullptr;
    size_t SIZE {0};
    void push(string value)
    {
        item *new_item = new item();
        new_item->data = value;
        new_item->link = top;
        top = new_item;
        SIZE ++ ;
    }
    string pop()
    {
        if(!top)
            return "";
        string rvalue = top->data;
        item *temp_ptr = top;
        top = top->link;
        delete temp_ptr;
        SIZE -- ;
        return rvalue;
    }
    string peek()
    {
        if(!top)
            return "";
        return top->data;
    }
    bool isEmpty()
    {
        if (top)
            return false;
        return true;
    }
    size_t size(){
        return SIZE; 
    }
};

struct oprndStack
{
    int top = -1;
    size_t SIZE = 0;
    double* array;
    void create(size_t size)
    {
        SIZE = size;
        array = new double[size];
        top = 0;
    }
    void push(double value){
        if(top == SIZE)
        {
            cout<<"Overflow Condition!"<<endl;
            exit(1);
        }
        top ++;
        array[top] = value ;
    }
    double pop(){
        if(top < 0)
        {
            cout<<"Underflow Condition!"<<endl;
            exit(1);
        }
        double rvalue = array[top];
        top --;
        return rvalue;
    }
    double peek(){
        if(isEmpty())
        {
            cout<<"Underflow Condition!"<<endl;
            exit(1);
        }
        return array[top];
    }
    size_t isEmpty(){
        if(top == -1 )
            return true;
        return false;
    }
};

#endif // STACK_H