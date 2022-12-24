#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <typeinfo>
#include <conio.h>
#include <vector>
#include "utility.h"
#include "structure.h"
using namespace std;
class Student{
    private:
        Utility* u;
        size_t no_of_records;
        size_t array_length;
        record* student;
    public:
        Student();
        ~Student();
        bool hasSpace();
        void createSpace();
        int is_key(string& rno);
        bool valid_rollno(string& rno);
        void display();
        void display(vector<record>& r);
        void input();
        void update();
        void remove();
        void generate_report();
};
#endif //STUDENT_H