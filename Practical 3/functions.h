#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <fstream>
#include <vector>
#include "structure.h"
using namespace std;

// getters & input
void get_name(string &name);                                        // allows only alphabets and white spaces to be a part of the string
void get_number(string &num);                                       // allows only numeric values to be a part of the string
void get_date(date &out_date, auto date_condition, date &com_date); // gets date according to the passed condition
void input_part_details(part &in_part);                             // used to input the data of a part
date current_date();                                                // gets the present date using time library
// checks and conditions
bool check_date_of_expiry(date &input, date &com_date); // condition for date of expiry
bool check_date_of_mfg(date &input, date &com_date);    // condition for date of manufacture
bool is_leap_year(const int &year);                     // checks for leap year
int check_valid_key(string &cID, string &pID);         // returns true if it finds key in the database
// converters
string date_to_str(date &in_date); // converts the date structure to a string
backup *backup_struct(part &prt);
part *load_struct(backup &bkp);
// displays functions
void show(part &prt); // single record
void show(part &prt, int srno); // single record
void display();       // all the records
// inserts a record in the data base
void insert();
void insert(int &index);
void insert(part &in_part);
// delete a record in the database
void remove();
void remove(size_t index);
// file handling and writing
void write_all_in_file();
void add_in_file(part &in_part);
void read_file();
// Sorting the list
void merge();
void merge_sort(node *list, int beg, int end);
// FUNCTIONS that work on the DOUBLY LINKED LIST
void add();
size_t count();
void delete_record();
void list_of_expired_parts();
void report();

#endif // FUNCTIONS_H