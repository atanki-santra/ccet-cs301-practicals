#ifndef TEXT_MANIPULATION_HPP
#define TEXT_MANIPULATION_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

struct element
{
    string word;
    size_t value{1};
};

struct node
{
    element data;
    node *link;
};

struct list
{
    node *start = nullptr;
    void create(string word)
    {
        start = new node();
        start->data.word = word;
        start->data.value = 1;
    }
    void searchAndUp(string word)
    {
        node *current = start;
        if (current->data.word == word)
        {
            current->data.value++;
            return;
        }
        node *ptr = current;
        current = current->link;
        while (current)
        {
            if (current->data.word == word)
                break;
            current = current->link;
            ptr = ptr->link;
        }
        if (!current)
        {
            node *newNode = new node();
            newNode->data.word = word;
            newNode->data.value = 1;
            ptr->link = newNode;
            return;
        }
        current->data.value++;
    }
    void print()
    {
        node *current = start;
        while (current)
        {
            cout << setw(30) << left << current->data.word << " : " << setw(10) << left << current->data.value << endl;
            current = current->link;
        }
    }
};

size_t countCharacters(string &text);
size_t countCharacters(string &text, char ch);
size_t countWords(string &text);
size_t countParagraphs(string &text);
size_t countSentences(string &text);
char toLowerCase(char ch);
void wordMap(string &text);
string processWord(string word);
void searchPattern(string text, string pattern);

#endif // TEXT_MANIPULATION_HPP