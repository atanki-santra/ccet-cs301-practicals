#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "binary-tree.h"
using namespace std;

int main()
{
     string str = "z-(v+((u/x)*y))";
     cout << string(64, '-') << endl
          << setw(63) << left << " | EXPRESSION TO BUILD THE TREE :" << '|' << endl
          << string(64, '-') << endl
          << "   " << str << endl
          << string(64, '-') << endl
          << setw(63) << left << " | CREATION OF TREE:" << '|' << endl
          << string(64, '-') << endl;
          binaryTree *expTree = createExpTree(str);
          ostringstream oss;
     string inExp, postExp, preExp;
     inorder(expTree->root, oss);
     inExp = oss.str();
     oss.str("");
     oss.clear();
     preorder(expTree->root, oss);
     preExp = oss.str();
     oss.str("");
     oss.clear();
     postorder(expTree->root, oss);
     postExp = oss.str();
     oss.str("");
     oss.clear();
     cout << string(64, '-') << endl
          << setw(63) << left << " | TRAVERSAL RESULTS :" << '|' << endl
          << string(64, '-') << endl
          << setw(30) << left << " | Postorder Traversal "
          << " : " << setw(30) << left << postExp << '|' << endl
          << setw(30) << left << " | InorderTraversal "
          << " : " << setw(30) << left << inExp << '|' << endl
          << setw(30) << left << " | Preorder Traversal "
          << " : " << setw(30) << left << preExp << '|' << endl
          << string(64, '-') << endl
          << string(64, '-') << endl
          << setw(63) << left << " | EVALUATION OF RESULT :" << '|' << endl
          << string(64, '-') << endl;
     double result = evaluatePrefixExp(preExp);
     cout << string(64, '-') << endl
          << setw(33) << left << " | RESULT " << ':' << setw(30) << left << result << endl
          << string(64, '-') << endl;
     return 0;
}