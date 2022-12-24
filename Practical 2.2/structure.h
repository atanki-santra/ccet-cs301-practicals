#ifndef STRUCTURE_H // include guards
#define STRUCTURE_H
#include <string>
#define START_YEAR 2000
#define FILE_NAME "employee-records.csv"
using namespace std;

/*
"employee_no": %d,
"name": "%s",
"father_name" : "%s",
"department" : "%s",
"date_of_joining" : {"date":%d,"month":%d,"year":%d},
"date_of_retirement" : {"date":%d,"month":%d,"year":%d},
"address" : {"house_no":"%s","village":"%s","town":"%s","city":"%s","state":"%s","PIN":%d,"country":"%s" 
*/
const char* EMPLOYEE_FORMAT_OUT = "{\"employee_no\": %d,\"name\": \"%s\",\"father_name\" : \"%s\",\"department\" : \"%s\",\"date_of_joining\" : {\"day\":%d,\"month\":%d,\"year\":%d},\"date_of_retirement\" : {\"day\":%d,\"month\":%d,\"year\":%d},\"address\" : {\"house_no\":\"%s\",\"village\":\"%s\",\"town\":\"%s\",\"city\":\"%s\",\"state\":\"%s\",\"PIN\":%d,\"country\":\"%s\"\n}";

const char* EMPLOYEE_FORMAT_IN = "{\"employee_no\": %d,\"name\": \"[^\"]\",\"father_name\" : \"[^\"]\",\"department\" : \"[^\"]\",\"date_of_joining\" : {\"day\":%d,\"month\":%d,\"year\":%d},\"date_of_retirement\" : {\"day\":%d,\"month\":%d,\"year\":%d},\"address\" : {\"house_no\":\"[^\"]\",\"village\":\"[^\"]\",\"town\":\"[^\"]\",\"city\":\"[^\"]\",\"state\":\"[^\"]\",\"PIN\":%d,\"country\":\"[^\"]\"\n}";

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
    date* date_of_joining = new date{1,1,START_YEAR};
    date* date_of_retirement = new date{1,1,START_YEAR+2};
    address* add = new address;
};

#endif //STRUCTURE_H