#ifndef STRUCTURE_H
#define STURCTURE_H
#define START_YEAR 1900
#define FILE_NAME "Inventory.dat"
#include <string>
using namespace std;

struct date{
    int day;
    int month;
    int year;
};

struct part{
    /*COMPOSITE KEY*/
    string company_ID {""}; //primary key
    string part_ID {""}; //primary key

    size_t quantity{0};
    string name{""};
    date mfg_date{1,1,1900};
    date exp_date{1,1,1900};
};

struct backup{
    char company_ID[20];
    char part_ID[20];
    size_t quantity;
    char name[30];
    date mfg_date;
    date exp_date;
};

//DOUBLY-LINKED-LIST

struct node{
    part data;
    node* prev {nullptr};
    node* next {nullptr};
};

static node* LP {nullptr};
static node* RP {nullptr};
static size_t list_len{0};

#endif //STRUCTURE_H