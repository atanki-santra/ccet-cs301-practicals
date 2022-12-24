#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include "structure.h"
using namespace std;

// Menu Display
void menu();

// Input
void input_employee(employee &e);
void input_address(address &a);
void get_name(string &name);
void get_date(date &out_date, auto date_condition, date &com_date);
void get_number(string &num);

// date checks & conditions
date current_date();
bool is_leap_year(const int &year);
bool check_date_of_joining(date &input, date &today);
bool check_date_of_retirement(date &input, date &doj);
bool check_valid_key(size_t &key);

// Display a record
void show(employee &e);

// Converters
string date_to_str(date &in_date);
string address_to_str(address &add);

// Operations on Linked-list
void add();
void insert();
void insert(size_t index);
void insert(employee &emp);
void remove();
void display();
void update();
void generate_report();
void list_destructor();

// Back-up functions
void load_list();
void write_all_in_file();
void read_file();
backup* bckp_struct(employee &emp);
employee* load_struct(backup &bkp);

#endif // FUNCTIONS_H