#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include "polishExp.h"
using namespace std;

int main()
{
    bool flag{true};
    do
    {
        system("CLS");
        cout << "Main Menu :" << endl
             << "1. Infix to Prefix" << endl
             << "2. Infix to Postfix" << endl
             << "3. Both of the Above" << endl
             << "4. EXIT " << endl;
        switch (getch())
        {
        case '1':
        {    
            system("CLS");
            string infixExp;
            cout << "Enter the expression" << endl;
            getline(cin, infixExp);
            string resultExp = toPrefix(infixExp);
            double resultExpValue = evaluatePrefixExp(resultExp);
            resultExp.erase(remove(resultExp.begin(), resultExp.end(), ' '), resultExp.end());
            cout << string(110, '-') << endl
                 << setw(25) << left << "Infix Expression"
                 << setw(25) << left << "Prefix Expression"
                 << setw(50) << left << "Result of expression with the given values" << endl
                 << string(110, '-') << endl
                 << setw(25) << left << infixExp
                 << setw(25) << left << resultExp
                 << setw(50) << left << resultExpValue << endl
                 << string(110, '-') << endl
                 << endl
                 << "Press Any key to start!..." << endl;
            getch();
        }
        break;
        case '2':
        {
            system("CLS");
            string infixExp;
            cout << "Enter the expression" << endl;
            getline(cin, infixExp);
            string resultExp = toPostfix(infixExp);
            double resultExpValue = evaluatePostfixExp(resultExp);
            resultExp.erase(remove(resultExp.begin(), resultExp.end(), ' '), resultExp.end());
            cout << string(110, '-') << endl
                 << setw(25) << left << "Infix Expression"
                 << setw(25) << left << "Postfix Expression"
                 << setw(50) << left << "Result of expression with the given values" << endl
                 << string(110, '-') << endl
                 << setw(25) << left << infixExp
                 << setw(25) << left << resultExp
                 << setw(50) << left << resultExpValue << endl
                 << string(110, '-') << endl
                 << endl
                 << "Press Any key to start!..." << endl;
            getch();
        }
        break;
        case '3':
        {
            string infixExp;
            system("CLS");
            cout << "Enter the expression" << endl;
            getline(cin, infixExp);
            string resultExpPre = toPrefix(infixExp);
            string resultExpPost = toPostfix(infixExp);
            system("CLS");
            double resultExpValuePre = evaluatePrefixExp(resultExpPre);
            system("CLS");
            double resultExpValuePost = evaluatePostfixExp(resultExpPost);
            system("CLS");
            resultExpPre.erase(remove(resultExpPre.begin(), resultExpPre.end(), ' '), resultExpPre.end());
            resultExpPost.erase(remove(resultExpPost.begin(), resultExpPost.end(), ' '), resultExpPost.end());
            cout << string(150, '-') << endl
                 << setw(25) << left << "Infix Expression"
                 << setw(25) << left << "Prefix Expression"
                 << setw(25) << left << "Postfix Expression"
                 << setw(25) << left << "Result of Prefix Exp"
                 << setw(25) << left << "Result of Postfix Exp" << endl
                 << string(150, '-') << endl
                 << setw(25) << left << infixExp
                 << setw(25) << left << resultExpPre
                 << setw(25) << left << resultExpPost
                 << setw(25) << left << resultExpValuePre 
                 << setw(25) << left << resultExpValuePost << endl
                 << string(150, '-') << endl
                 << endl
                 << "Press Any key to start!..." << endl;
            getch();
            getch();
        }
        break;
        case '4':
            flag = false;
        }
    } while (flag);
    return 0;
}