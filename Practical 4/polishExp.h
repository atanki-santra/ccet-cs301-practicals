#ifndef POLISHEXP_H
#define POLISHEXP_H

#include "stack.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

double power(double a , double b);
bool isNumeric(string &str);
bool isAlphanumeric(string &str);
bool isOprtr(string &str);
void reverse(string &exp);

int precedence(string optr);
void findAndReplaceAll(string& data, string toSearch, string replaceStr);
struct stack expToStack(string& exp);
void expForPostfix(string& exp);
void expForPrefix(string& exp);

string toPostfix(string& infixExp);
string toPrefix(string& infixExp);
double evaluatePostfixExp(string exp); 
double evaluatePrefixExp(string exp);

#endif //POLISHEXP_H