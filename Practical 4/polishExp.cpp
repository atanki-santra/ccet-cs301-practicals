#include "polishExp.h"

double power(double a , double b)
{
    double result {1};
    for(size_t i{0};i<b;i++)
        result*=a;
    return result;
} 

bool isNumeric(string &str)
{
    for (auto ch : str)
        if (ch < '0' || ch > '9')
            return false;
    return true;
}

bool isAlphanumeric(string &str)
{
    for (auto ch : str)
        if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z'))
            return false;
    return true;
}

bool isOprtr(string &str)
{
    char oprtrs[5] = {'+', '-', '*', '/', '^'};
    if (str.length() > 1)
        return false;
    for (auto oprtr : oprtrs)
        if (str[0] == oprtr)
            return true;
    return false;
}

int precedence(string optr)
{
    if (optr == "(" || optr == ")")
        return -1;
    if (optr == "+" || optr == "-")
        return 1;
    if (optr == "*" || optr == "/")
        return 2;
    if (optr == "^")
        return 3;
    return 0;
}

void reverse(string &exp)
{
    struct stack str;
    for (size_t i{0}; i < exp.length(); i++)
        str.push(string(1, exp[i]));
    exp = "";
    while (!str.isEmpty())
        exp += str.pop();
}

void expForPostfix(string &exp)
{
    findAndReplaceAll(exp, "+", " + ");
    findAndReplaceAll(exp, "-", " - ");
    findAndReplaceAll(exp, "*", " * ");
    findAndReplaceAll(exp, "/", " / ");
    findAndReplaceAll(exp, "(", " ( ");
    findAndReplaceAll(exp, ")", " ) ");
    findAndReplaceAll(exp, "^", " ^ ");
    reverse(exp);
}

void expForPrefix(string &exp)
{
    findAndReplaceAll(exp, "+", " + ");
    findAndReplaceAll(exp, "-", " - ");
    findAndReplaceAll(exp, "*", " * ");
    findAndReplaceAll(exp, "/", " / ");
    findAndReplaceAll(exp, "(", " ( ");
    findAndReplaceAll(exp, ")", " ) ");
    findAndReplaceAll(exp, "^", " ^ ");
}

void findAndReplaceAll(string &data, string toSearch, string replaceStr)
{
    size_t pos = data.find(toSearch);
    while (pos != string::npos)
    {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

struct stack expToStack(string &exp)
{
    struct stack tokens;
    istringstream iss(exp);
    while (!iss.eof())
    {
        string temp;
        getline(iss, temp, ' ');
        if (temp == "")
            continue;
        tokens.push(temp);
    }
    return tokens;
}

string toPostfix(string &infixExp)
{
    string exp = infixExp;
    expForPostfix(exp);
    struct stack tokens = expToStack(exp);
    struct stack placeholder;
    string postfixExp = "";
    while (!tokens.isEmpty())
    {
        if (tokens.peek() == "(")
            placeholder.push(tokens.pop());
        else if (tokens.peek() == ")")
        {
            tokens.pop();
            while ((placeholder.peek() != "(") && (!placeholder.isEmpty()))
                postfixExp = postfixExp + placeholder.pop() + " ";
            placeholder.pop();
        }
        else if (!(tokens.peek() == "+" || tokens.peek() == "-" || tokens.peek() == "*" || tokens.peek() == "/" || tokens.peek() == "^" || placeholder.peek()=="("))
            postfixExp = postfixExp + tokens.pop() + " ";
        else
        {
            while (!placeholder.isEmpty() && (precedence(tokens.peek()) <= precedence(placeholder.peek())))
            {
                postfixExp = postfixExp + placeholder.pop() + " ";
            }    
            placeholder.push(tokens.pop());
        }
    }
    while (!placeholder.isEmpty())
        postfixExp = postfixExp + placeholder.pop() + " ";
    return postfixExp;
}

string toPrefix(string &infixExp)
{
    string exp = infixExp;
    expForPrefix(exp);
    struct stack tokens = expToStack(exp);
    struct stack placeholder;
    string prefixExp = "";
    while (!tokens.isEmpty())
    {
        if (tokens.peek() == ")")
            placeholder.push(tokens.pop());
        else if (tokens.peek() == "(")
        {
            tokens.pop();
            while ((placeholder.peek() != ")") && (!placeholder.isEmpty()))
                prefixExp = prefixExp + placeholder.pop() + " ";
            placeholder.pop();
        }
        else if (!(tokens.peek() == "+" || tokens.peek() == "-" || tokens.peek() == "*" || tokens.peek() == "/" || tokens.peek() == "^"))
            prefixExp = prefixExp + tokens.pop() + " ";
        else
        {
            while (!placeholder.isEmpty() && (precedence(tokens.peek()) < precedence(placeholder.peek())))
                prefixExp = prefixExp + placeholder.pop() + " ";
            placeholder.push(tokens.pop());
        }
    }
    while (!placeholder.isEmpty())
        prefixExp = prefixExp + placeholder.pop() + " ";
    reverse(prefixExp);
    return prefixExp;
}

double evaluatePostfixExp(string exp)
{
    istringstream iss(exp);
    string oprnd;
    double value;
    struct oprndStack valueStack;
    valueStack.create(exp.length());
    while (getline(iss, oprnd, ' '))
    {
        if (isNumeric(oprnd))
            valueStack.push(stoi(oprnd));
        else if (isAlphanumeric(oprnd))
        {
            cout << "Enter value of " << oprnd << " : ";
            cin >> value;
            cin.ignore();
            valueStack.push(value);
        }
        else if (isOprtr(oprnd))
        {
            double val1 =valueStack.pop();
            double val2 =valueStack.pop();
            switch (oprnd[0])
            {
                case '+':
                    valueStack.push(val2 + val1);
                break;
                case '-':
                    valueStack.push(val2 - val1);
                break;
                case '*':
                    valueStack.push(val2 * val1);
                break;
                case '/':
                    valueStack.push(val2 / val1);
                break;
                case '^':
                    valueStack.push(power(val2 , val1));
                break;
            }
        }
    }
    return valueStack.pop();
}

double evaluatePrefixExp(string exp)
{
    reverse(exp);
    istringstream iss(exp);
    string oprnd;
    double value;
    struct oprndStack valueStack;
    valueStack.create(exp.length());

    while (getline(iss, oprnd, ' '))
    {
        if (isNumeric(oprnd))
            valueStack.push(stoi(oprnd));
        else if (isAlphanumeric(oprnd))
        {
            cout << "Enter value of " << oprnd << " : ";
            cin >> value;
            cin.ignore();
            valueStack.push(value);
        }
        else if (isOprtr(oprnd))
        {
            double val1 =valueStack.pop();
            double val2 =valueStack.pop();
            switch (oprnd[0])
            {
                case '+':
                    valueStack.push(val1 + val2);
                break;
                case '-':
                    valueStack.push(val1 - val2);
                break;
                case '*':
                    valueStack.push(val1 * val2);
                break;
                case '/':
                    valueStack.push(val1 / val2);
                break;
                case '^':
                    valueStack.push(power(val1 , val2));
                break;
            }
        }
    }
    return valueStack.pop();
}