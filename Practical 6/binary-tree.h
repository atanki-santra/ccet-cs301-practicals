#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "structure.h"
#include "polishExp.h"
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

struct binaryTree
{
    BT root;
    size_t numOfNodes = 0;
    void create(string info)
    {
        if (root)
        {
            printf("Root Tree already defined");
            return;
        }
        BT newNode = new node();
        newNode->info = info;
        root = newNode;
        numOfNodes++;
    }
    void add(string info, size_t index)
    {
        BT newNode = new node();
        newNode->info = info;
        intStack istck;
        istck.create((int)ceil(log2(index)));
        size_t posn = index;
        while (posn != 1)
        {
            istck.push(posn);
            posn = posn / 2;
        }
        BT ptr{root};
        while (istck.peek() != index)
        {
            // cout<<istck.peek()<<endl;
            if (istck.pop() % 2 == 0)
                ptr = ptr->leftChild;
            else
                ptr = ptr->rightChild;
        }
        // cout<<ptr->info<<"       ";
        if (istck.pop() % 2 == 0)
            ptr->leftChild = newNode;
        else
            ptr->rightChild = newNode;
        cout << setw(15) << left << "   Added value at index : " << setw(5) << index  << "Updated Node :   ";
        show(ptr);
        cout<<endl;
        // cout<<info <<" added at "<<index<<endl;
        numOfNodes++;
    }
    void show(BT ptr)
    {
        if (!ptr->leftChild)
            cout << "NIL"
                 << " <- ";
        else
            cout << ptr->leftChild->info << " <- ";
        cout << ptr->info << " -> ";
        if (!ptr->rightChild)
            cout << "NIL";
        else
            cout << ptr->rightChild->info;
    }
};

binaryTree *createExpTree(string &exp)
{
    binaryTree *expTree = new binaryTree();
    string expnew = toPrefix(exp);
    reverse(expnew);
    struct stack expStck = expToStack(expnew);
    string holder = expStck.pop();
    expTree->create(holder);
    int count = 0, routeNode = 1, idx;
    intStack rnStck, cntStck;
    rnStck.create(((int)ceil(log2(expStck.size()))) + 1);
    cntStck.create(rnStck.SIZE);
    rnStck.push(routeNode);
    while (!expStck.isEmpty())
    {
        if (isAlphanumeric(expStck.peek())) // IF NOT AN OPERATOR
        {
            expTree->add(expStck.pop(), (routeNode * 2 + count));
            count++;
            if (count == 2)
            {
                while (count != 1)
                {
                    if (expStck.isEmpty())
                        break;
                    routeNode = rnStck.pop();
                    count = cntStck.pop() + 1;
                }
            }
            continue;
        }
        if (isOprtr(expStck.peek()))
        {
            expTree->add(expStck.pop(), (routeNode * 2 + count));
            rnStck.push(routeNode);
            cntStck.push(count);
            routeNode = (routeNode * 2 + count);
            count = 0;
        }
    }
    return expTree;
}

void preorder(BT expTree, ostringstream &oss)
{
    if (expTree == nullptr)
        return;
    oss << expTree->info + " ";
    preorder(expTree->leftChild, oss);
    preorder(expTree->rightChild, oss);
}

void inorder(BT expTree, ostringstream &oss)
{
    if (expTree == nullptr)
        return;
    inorder(expTree->leftChild, oss);
    oss << expTree->info << " ";
    inorder(expTree->rightChild, oss);
}

void postorder(BT expTree, ostringstream &oss)
{
    if (expTree == nullptr)
        return;
    postorder(expTree->leftChild, oss);
    postorder(expTree->rightChild, oss);
    oss << expTree->info << " ";
}
#endif // BINARYTREE_H