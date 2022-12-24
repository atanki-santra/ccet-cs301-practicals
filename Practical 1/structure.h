#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <string>
#include <iostream>
#include <iomanip>
#define FILE_NAME "student-records.csv"
#define START_YEAR 1959
#define PRESENT_YEAR 2022
#define CSE_CODE 3
#define ECE_CODE 5
#define CIVIL_CODE 2
#define MECH_CODE 1
using namespace std;
struct record
{
    string roll_no{""};//primary key
    //format: CO${year_of_admission}${branch}${serial_no(lexographical order)}
    string name{""};
    string father_name{""};
    string date_of_birth{""};//format: dd/mm/yyyy
    string branch{""};
    unsigned int year_of_admission{0};
    unsigned int year_of_passing{0};//tentative
    string district{""};
    string state {""};
    unsigned int pin{0};//6 digit code
    string country{""};
};
#endif //STRUCTURE_H