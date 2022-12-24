#ifndef STRUCTURE_H // include guards
#define STRUCTURE_H
#include <string>
#define START_YEAR 2000
#define FILE_NAME "data.bin"
using namespace std;

struct address{
    string house_no{""};
    string village{""};
    string town{""};
    string city{""};
    string state{""};
    unsigned int PIN{0};
    string country{""};
};

struct date{
    int day;
    int month;
    int year;
};

struct employee{
    size_t employee_no{0};
    string name{""};
    string father_name{""};
    string department{""};
    date date_of_joining{1,1,START_YEAR};
    date date_of_retirement{1,1,START_YEAR+2};
    address add;
};

struct employee_list{
    employee data;
    employee_list* next{nullptr};
};


struct backup{
    size_t employee_no{0};
    char name[50];
    char father_name[50];
    char department[50];
    date date_of_joining{1,1,START_YEAR};
    date date_of_retirement{1,1,START_YEAR+2};
    address add;
};

// Static Variables
static employee_list *start{nullptr};
static size_t list_len;

#endif //STRUCTURE_H