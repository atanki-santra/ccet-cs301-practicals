#ifndef UTILITY_H
#define UTILITY_H
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "structure.h"
using namespace std;
class Utility{
    public:
        void string_to_record(string& line,record&);
        bool is_leap_year(const int& year);
        void add_in_file(const record& r);
        void write_file(record* r, size_t len);
        size_t count(const string& file_name);
        void show(const record& r);
};
#endif //FILE_HANDLING_H
