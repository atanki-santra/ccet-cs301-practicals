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

struct employee_list
{
    employee data;
    employee_list *next{nullptr};
};

/*
FUNCTION DECLARATIONS:
*/

// Menu Display
void menu();

// Input
void input_employee(employee &e);
void input_address(address &a);
void get_name(string &name);
void get_date(date *out_date, auto date_condition, date *com_date);
void get_number(string &num);

// copy
void copy(employee &out_emp, employee &in_emp);

// date checks & conditions
date current_date();
bool is_leap_year(const int &year);
bool check_date_of_joining(date &input, date *today);
bool check_date_of_retirement(date &input, date *doj);
bool check_valid_key(size_t &key);

// Display a record
void show(employee &e);

// Converters
string date_to_str(date *in_date);
string address_to_str(address *add);
employee *str_to_employee(string &record);
date *str_to_date(string &in_date);
address *str_to_address(string &in_address);

// Operations on Linked-list
void add();
void insert();
void insert(size_t index);
void insert(employee &emp);
void insert(employee *emp);
void remove();
void display();
void update();
void generate_report();
void load_list();
void list_destructor();
void read_file();

// Back-up functions
void add_in_file(employee &emp);
void write_all_in_file();

// Static Variables
static employee_list *start{nullptr};
static size_t list_len;

int main()
{
    list_len = 0;
    bool flag = true;
    do
    {
        system("CLS");
        menu();
        switch (getch())
        {
        case 49:
        {
            system("CLS");
            cout << "INPUT WINDOW:\n"
                 << endl;
            add();
            cout << "\nPress any key to continue...." << endl;
            getch();
        }
        break;
        case 50:
        {
            system("CLS");
            cout << "UPDATION WINDOW:\n"
                 << endl;
            update();
            cout << "\nPress any key to continue...." << endl;
            getch();
        }
        break;
        case 51:
        {
            system("CLS");
            cout << "DELETION WINDOW:\n"
                 << endl;
            remove();
            cout << "\nPress any key to continue...." << endl;
            getch();
        }
        break;
        case 52:
        {
            system("CLS");
            cout << "GENERATION OF REPORT:\n"
                 << endl;
            generate_report();
            cout << "\nPress any key to continue...." << endl;
            getch();
        }
        break;
        case 53:
        {
            system("CLS");
            cout << "RECORDS OF ALL EMPLOYEES:\n"
                 << endl;
            display();
            cout << "\nPress any key to continue...." << endl;
            getch();
        }
        break;
        case 54:
        {
            flag = false;
        }
        break;
        case 55:
        {
            cout << "write in file data.bin" << endl;
            write_all_in_file();
        }
        break;
        case 56:
        {
            cout << "read from fle data.bin" << endl;
            read_file();
        }
        break;
        }
    } while (flag);
    list_destructor();
    return 0;
}

/*
FUNCTION DEFINITIONS
*/

void menu()
{
    cout << "  ______                 _                         _____        _        _                    " << endl;
    cout << " |  ____|               | |                       |  __ \\      | |      | |                   " << endl;
    cout << " | |__   _ __ ___  _ __ | | ___  _   _  ___  ___  | |  | | __ _| |_ __ _| |__   __ _ ___  ___ " << endl;
    cout << " |  __| | '_ ` _ \\| '_ \\| |/ _ \\| | | |/ _ \\/ _ \\ | |  | |/ _` | __/ _` | '_ \\ / _` / __|/ _ \\" << endl;
    cout << " | |____| | | | | | |_) | | (_) | |_| |  __/  __/ | |__| | (_| | || (_| | |_) | (_| \\__ \\  __/" << endl;
    cout << " |______|_| |_| |_| .__/|_|\\___/ \\__, |\\___|\\___| |_____/ \\__,_|\\__\\__,_|_.__/ \\__,_|___/\\___|" << endl;
    cout << "                  | |             __/ |                                                       " << endl;
    cout << "                  |_|            |___/                                                        \n\n"
         << endl;
    cout << "1. Add a record" << endl
         << "2. Update a record" << endl
         << "3. Delete a record" << endl
         << "4. Generate a report" << endl
         << "5. Display all records" << endl
         << "6. Exit" << endl
         << "7. write in bin file " << endl
         << "8. read from bin file " << endl;
}

bool is_leap_year(const int &year)
{
    if (year % 4 == 0)
    {
        return (year % 100 != 0 || year % 400 == 0);
    }
    return false;
}

date current_date()
{
    date today;
    time_t now = time(0);
    tm *current_date = localtime(&now);
    today.year = 1900 + current_date->tm_year;
    today.month = current_date->tm_mon + 1;
    today.day = current_date->tm_mday;
    return today;
}

bool check_date_of_joining(date &input, date *today)
{
    if (today->year < input.year)
        return false;
    if (today->year == input.year && today->month < input.month)
        return false;
    if (today->year == input.year && today->month == input.month && today->day <= input.day)
        return false;
    return true;
}

bool check_date_of_retirement(date &input, date *doj)
{
    if (doj->year > input.year)
        return false;
    if (doj->year == input.year && doj->month > input.month)
        return false;
    if (doj->year == input.year && doj->month == input.month && doj->day > input.day)
        return false;
    return true;
}

void get_date(date *out_date, auto date_condition, date *com_date)
{
    do
    {
        date in_date;
        cout << "Enter year : ";
        do
        {
            cin >> in_date.year;
            if (in_date.year <= START_YEAR)
            {
                cout << "Invalid Year!" << endl;
                continue;
            }
            break;
        } while (true);
        cout << "Enter month : ";
        do
        {
            cin >> in_date.month;
            if (in_date.month > 12 || in_date.month < 1)
            {
                cout << "Invalid Month! Re-Enter" << endl;
                continue;
            }
            break;
        } while (true);
        cout << "Enter Date : ";
        {
            int days_in_month[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            do
            {
                cin >> in_date.day;
                if (is_leap_year(in_date.year))
                    days_in_month[1] = 29;
                if (!(in_date.day >= days_in_month[in_date.month - 1] && in_date.day > 0))
                    break;
                cout << "Invalid Date! Re-Enter" << endl;
            } while (true);
        }
        if (!date_condition(in_date, com_date))
        {
            cout << "Date is either Invalid! Re-Enter!" << endl;
            continue;
        }
        break;
    } while (true);
    cin.ignore();
}

void input_address(address *a)
{
    cout << "House Number :";
    getline(cin, a->house_no);
    cout << "Village/Town/Street :";
    getline(cin, a->village);
    cout << "Post Office/Town/Circle :";
    getline(cin, a->town);
    cout << "City :";
    get_name(a->city);
    cout << "State :";
    get_name(a->state);
    cout << "PIN :";
    {
        do
        {
            string temp;
            get_number(temp);
            a->PIN = stoi(temp);
            if (a->PIN > 999999 && a->PIN < 100000)
                continue;
            break;
        } while (true);
    }
    cout << "Country :";
    get_name(a->country);
}

void get_number(string &num)
{
    do
    {
        getline(cin, num);
        size_t i{0};
        for (; i < num.length(); i++)
        {
            if (!(num[i] >= '0' && num[i] <= '9'))
                break;
        }
        if (i < num.length())
        {
            cout << "Invalid Input! Re-Enter! " << endl;
            continue;
        }
        break;
    } while (true);
}

bool check_valid_key(size_t &key)
{
    employee_list *current = start;
    if (!current)
        return true;
    while (current->next)
    {
        if (current->data.employee_no == key)
            return false;
        current = current->next;
    }
    return true;
}

void input_employee(employee &e)
{
    cout << "ENTER THE DATA OF THE EMPLOYEE:\n"
         << endl;
    cout << "Enter employee's number :";
    do
    {
        string temp;
        get_number(temp);
        e.employee_no = stoi(temp);
        if (!check_valid_key(e.employee_no))
        {
            cout << "Employee Number already exists! Re-Enter!" << endl;
            continue;
        }
        break;
    } while (true);
    cout << "Enter employee's name :";
    get_name(e.name);
    cout << "Enter father's name :";
    get_name(e.father_name);
    cout << "Enter department :";
    get_name(e.department);
    cout << "Enter date of joining :" << endl;
    {
        date today = current_date();
        get_date(e.date_of_joining, check_date_of_joining, &today);
    }
    cout << "Enter date of retirement :" << endl;
    get_date(e.date_of_retirement, check_date_of_retirement, e.date_of_joining);
    cout << "Enter Address:" << endl;
    input_address(e.add);
}

void insert()
{
    employee_list *new_employee = new employee_list;
    input_employee(new_employee->data);
    if (!start)
    {
        start = new_employee;
        start->next = nullptr;
    }
    else
    { // adds element to the end of the list
        employee_list *current = start;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_employee;
        new_employee->next = nullptr;
    }
    list_len++;
    add_in_file(new_employee->data);
}

void insert(size_t index)
{
    employee_list *new_employee = new employee_list;
    input_employee(new_employee->data);
    employee_list *current = start;
    if (index == 0)
    {
        new_employee->next = start;
        start = new_employee;
        write_all_in_file();
    }
    else
    {
        for (size_t i{0}; i < index; i++)
        {
            current = current->next;
        }
        new_employee->next = current->next;
        current->next = new_employee;
        add_in_file(new_employee->data);
    }
    list_len++;
}

void insert(employee *emp)
{
    employee_list *new_employee = new employee_list;
    new_employee->data = *emp;
    if (!start)
    {
        start = new_employee;
        start->next = nullptr;
    }
    else
    { // adds element to the end of the list
        employee_list *current = start;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_employee;
        new_employee->next = nullptr;
    }
    list_len++;
}

void remove()
{
    do
    {
        size_t emp_no;
        cout << "Enter Employee Number :" << endl;
        do
        {
            string temp;
            get_number(temp);
            emp_no = stoi(temp);
            if (check_valid_key(emp_no))
            {
                cout << "Invalid Employee Number" << endl;
                continue;
            }
            break;
        } while (true);
        employee_list *current = start;
        employee_list *prev = start;
        if (current->data.employee_no == emp_no)
        {
            start = current->next;
        }
        else
        {
            current = current->next;
            while (!(current->data.employee_no == emp_no))
            {
                current = current->next;
                prev = prev->next;
            }
            prev->next = current->next;
        }
        {
            char choice;
            cout << "\nDo you want to delete the following record?(Y/N)" << endl;
            show(current->data);
            cin >> choice;
            do
            {
                if (choice == 'n' || choice == 'N')
                    break;
                else if (choice == 'y' || choice == 'Y')
                {
                    list_len--;
                    delete current->data.date_of_joining;
                    delete current->data.date_of_retirement;
                    delete current->data.add;
                    delete current;
                    cout << "The record has been deleted successfully!" << endl;
                    write_all_in_file();
                    return;
                }
            } while (true);
        }
    } while (true);
}

void display()
{
    cout << setw(12) << left << "Emp.No " << setw(20) << left << "Name" << setw(20) << left << "Father's Name" << setw(12) << left << "Date of " << setw(20) << left << "Department" << setw(12) << left << "Date of " << setw(50) << left << "Address" << endl;
    cout << setw(12) << left << " " << setw(20) << left << " " << setw(20) << left << " " << setw(12) << left << "Joining" << setw(20) << left << " " << setw(12) << left << "Retirement" << endl;
    cout << string(160, '_') << endl;
    employee_list *current = start;
    while (current)
    {
        show(current->data);
        current = current->next;
    }
}

string date_to_str(date *in_date)
{
    ostringstream oss;
    oss << in_date->day << "/" << in_date->month << "/" << in_date->year;
    return oss.str();
}

string address_to_str(address *add)
{
    ostringstream oss;
    oss << add->house_no << "," << add->village << "," << add->town << "," << add->city << "," << add->state << "," << add->PIN << "," << add->country;
    return oss.str();
}

void show(employee &e)
{
    cout << setw(12) << left << e.employee_no << setw(20) << left << e.name << setw(20) << left << e.father_name << setw(12) << left << date_to_str(e.date_of_joining) << setw(20) << left << e.department << setw(12) << left << date_to_str(e.date_of_retirement) << address_to_str(e.add) << endl;
}

void update()
{
    size_t emp_no;
    cout << "Enter Employee Number :" << endl;
    do
    {
        string temp;
        get_number(temp);
        emp_no = stoi(temp);
        if (check_valid_key(emp_no))
        {
            cout << "Invalid Employee Number" << endl;
            continue;
        }
        break;
    } while (true);
    employee *emp;
    employee_list *current = start;
    while (current)
    {
        if (current->data.employee_no == emp_no)
        {
            emp = &(current->data);
            break;
        }
        current = current->next;
    }

    bool flag{true};
    do
    {
        system("CLS");
        cout << "Updating data of EMPLOYEE NO. :" << emp_no << endl
             << endl;
        cout << "Choose the attribute you want to update :\n1.Name\n2.Father's Name\n3.Date of Joining\n4.Department\n5.Date of Retirement\n6.Address\n7.Exit" << endl;
        switch (getch())
        {
        case 49:
        {
            cout << "Enter new name: ";
            get_name(emp->name);
            cout << "The name is Updated to : " << emp->name << endl;
        }
        break;
        case 50:
        {
            cout << "Enter new father's name: ";
            get_name(emp->father_name);
            cout << "The father's name is Updated to : " << emp->father_name << endl;
        }
        break;
        case 51:
        {
            cout << "Enter new date of joining: " << endl;
            {
                date today = current_date();
                get_date(emp->date_of_joining, check_date_of_joining, &today);
            }
            cout << "Date of Joining is Updated to : " << date_to_str(emp->date_of_joining);
        }
        break;
        case 52:
        {
            cout << "Enter new Department: ";
            get_name(emp->department);
            cout << "The Department is Updated to : " << emp->department << endl;
        }
        break;
        case 53:
        {
            cout << "Enter new date of retirement: " << endl;
            {
                date today = current_date();
                get_date(emp->date_of_retirement, check_date_of_retirement, emp->date_of_joining);
            }
            cout << "Date of Retirement is Updated to : " << date_to_str(emp->date_of_retirement);
        }
        break;
        case 54:
        {
            cout << "Enter new Address: " << endl;
            input_address(emp->add);
            cout << "Address has been Updated to : " << address_to_str(emp->add);
        }
        break;
        case 55:
        {
            flag = false;
        }
        break;
        }
        getch();
    } while (flag);
    write_all_in_file();
}

void list_destructor()
{
    if (start)
    {
        employee_list *current = start;
        employee_list *fwd = current->next;
        do
        {
            fwd = current->next;
            delete current->data.date_of_joining;
            delete current->data.date_of_retirement;
            delete current->data.add;
            delete current;
            current = fwd;
        } while (fwd->next);
        delete current->data.date_of_joining;
        delete current->data.date_of_retirement;
        delete current->data.add;
        delete current;
    }
}

void add()
{
    bool flag{true};
    do
    {
        system("CLS");
        cout << "Enter the position you want to add the record at :\n\t1.Head\n\t2.At a particular index\n\t3.Tail\n\t4.Exit" << endl;
        switch (getch())
        {
        case 49:
            insert((int)0);
            break;
        case 50:
        {
            int index{0};
            cout << "Enter the index where you want to add the index : ";
            do
            {
                cin >> index;
                if (index < 1 || index > list_len)
                {
                    cout << "Invalid Index" << endl;
                    continue;
                }
                break;
            } while (true);
            insert(index - 1);
        }
        break;
        case 51:
            insert();
            break;
        case 52:
            flag = false;
            break;
        }
    } while (flag);
}

void load_list()
{
    ifstream fin;
    fin.open(FILE_NAME);
    if (!fin)
    {
        cout << "Error in Opening the records file!" << endl;
        exit(1);
    }
    while (!fin.eof())
    {
        employee *emp;
        string record;
        getline(fin, record);
        emp = str_to_employee(record);
        insert(emp);
    }
    fin.close();
}

employee *str_to_employee(string &record)
{
    employee *emp = new employee;
    istringstream iss(record);
    string temp{};
    getline(iss, temp, ',');
    emp->employee_no = stoi(temp);
    getline(iss, emp->name, ',');
    getline(iss, emp->father_name, ',');
    getline(iss, temp, ',');
    emp->date_of_joining = str_to_date(temp);
    getline(iss, emp->department, ',');
    getline(iss, temp, ',');
    emp->date_of_retirement = str_to_date(temp);
    getline(iss, temp);
    emp->add = str_to_address(temp);
    return emp;
}

date *str_to_date(string &in_date)
{
    date *out_date = new date;
    istringstream iss(in_date);
    string temp{};
    getline(iss, temp, '/');
    out_date->day = stoi(temp);
    getline(iss, temp, '/');
    out_date->month = stoi(temp);
    getline(iss, temp);
    out_date->year = stoi(temp);
    return out_date;
}

address *str_to_address(string &in_address)
{
    address *out_address = new address;
    istringstream iss(in_address);
    getline(iss, out_address->house_no, ',');
    getline(iss, out_address->village, ',');
    getline(iss, out_address->town, ',');
    getline(iss, out_address->city, ',');
    getline(iss, out_address->state, ',');
    string temp{};
    getline(iss, temp, ',');
    out_address->PIN = stoi(temp);
    getline(iss, out_address->country);
    return out_address;
}

void generate_report()
{
    bool flag{true};
    do
    {
        system("CLS");
        cout << "Generate report according to :\n1.Common city, state and country\n2.Common Date of Retirement\n3.Common Date of Joining\n4.Exit" << endl;
        switch (getch())
        {
        case 49:
        {
            if (!start)
            {
                cout << "There are no Elements in the List!" << endl;
                break;
            }
            string city{""}, state{""}, country{""};
            cout << "Enter the city to search for :" << endl;
            get_name(city);
            cout << "Enter the state to search for :" << endl;
            get_name(state);
            cout << "Enter the country to search for :" << endl;
            get_name(country);
            cout << "\n\nThe Employees with the above data are :\n"
                 << endl;
            employee_list *current = start;
            cout << setw(12) << left << "Emp.No " << setw(20) << left << "Name" << setw(20) << left << "Father's Name" << setw(12) << left << "Date of " << setw(20) << left << "Department" << setw(12) << left << "Date of " << setw(50) << left << "Address" << endl;
            cout << setw(12) << left << " " << setw(20) << left << " " << setw(20) << left << " " << setw(12) << left << "Joining" << setw(20) << left << " " << setw(12) << left << "Retirement" << endl;
            cout << string(160, '_') << endl;
            while (current)
            {
                if (current->data.add->city == city && current->data.add->state == state && current->data.add->country == country)
                    show(current->data);
                current = current->next;
            }
            cout << "\nPress Any Key to Continue..." << endl;
            getch();
        }
        break;
        case 50:
        {
            if (!start)
            {
                cout << "There are no Elements in the List!" << endl;
                break;
            }
            cout << "Enter date to be searched for :" << endl;
            date in_date;
            cout << "Enter year : ";
            do
            {
                cin >> in_date.year;
                if (in_date.year < START_YEAR)
                {
                    cout << "Invalid Year!" << endl;
                    continue;
                }
                break;
            } while (true);
            cout << "Enter month : ";
            do
            {
                cin >> in_date.month;
                if (in_date.month > 12 || in_date.month < 1)
                {
                    cout << "Invalid Month! Re-Enter" << endl;
                    continue;
                }
                break;
            } while (true);
            cout << "Enter Date : ";
            {
                int days_in_month[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                do
                {
                    cin >> in_date.day;
                    if (is_leap_year(in_date.year))
                        days_in_month[1] = 29;
                    if (!(in_date.day >= days_in_month[in_date.month - 1] && in_date.day > 0))
                        break;
                    cout << "Invalid Date! Re-Enter" << endl;
                } while (true);
            }
            cout << "\n\nReport on Employees retiring on the same date :" << endl;
            employee_list *current = start;
            cout << setw(12) << left << "Emp.No " << setw(20) << left << "Name" << setw(20) << left << "Father's Name" << setw(12) << left << "Date of " << setw(20) << left << "Department" << setw(12) << left << "Date of " << setw(50) << left << "Address" << endl;
            cout << setw(12) << left << " " << setw(20) << left << " " << setw(20) << left << " " << setw(12) << left << "Joining" << setw(20) << left << " " << setw(12) << left << "Retirement" << endl;
            cout << string(160, '_') << endl;
            while (current)
            {
                if (current->data.date_of_retirement->day == in_date.day && current->data.date_of_retirement->month == in_date.month && current->data.date_of_retirement->year == in_date.year)
                    show(current->data);
                current = current->next;
            }
            cout << "\nPress Any Key to Continue..." << endl;
            getch();
        }
        break;
        case 51:
        {
            if (!start)
            {
                cout << "There are no Elements in the List!" << endl;
                break;
            }
            cout << "Enter date to be searched for :" << endl;
            date in_date;
            cout << "Enter year : ";
            do
            {
                cin >> in_date.year;
                if (in_date.year < START_YEAR)
                {
                    cout << "Invalid Year!" << endl;
                    continue;
                }
                break;
            } while (true);
            cout << "Enter month : ";
            do
            {
                cin >> in_date.month;
                if (in_date.month > 12 || in_date.month < 1)
                {
                    cout << "Invalid Month! Re-Enter" << endl;
                    continue;
                }
                break;
            } while (true);
            cout << "Enter Date : ";
            {
                int days_in_month[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                do
                {
                    cin >> in_date.day;
                    if (is_leap_year(in_date.year))
                        days_in_month[1] = 29;
                    if (!(in_date.day >= days_in_month[in_date.month - 1] && in_date.day > 0))
                        break;
                    cout << "Invalid Date! Re-Enter" << endl;
                } while (true);
            }
            cout << "\n\nReport on Employees who joined the organisation on the same date :" << endl;
            employee_list *current = start;
            cout << setw(12) << left << "Emp.No " << setw(20) << left << "Name" << setw(20) << left << "Father's Name" << setw(12) << left << "Date of " << setw(20) << left << "Department" << setw(12) << left << "Date of " << setw(50) << left << "Address" << endl;
            cout << setw(12) << left << " " << setw(20) << left << " " << setw(20) << left << " " << setw(12) << left << "Joining" << setw(20) << left << " " << setw(12) << left << "Retirement" << endl;
            cout << string(160, '_') << endl;
            while (current)
            {
                if (current->data.date_of_joining->day == in_date.day && current->data.date_of_joining->month == in_date.month && current->data.date_of_joining->year == in_date.year)
                    show(current->data);
                current = current->next;
            }
            cout << "\nPress Any Key to Continue..." << endl;
            getch();
        }
        break;
        case 52:
        {
            flag = false;
        }
        break;
        }
    } while (flag);
}

void get_name(string &name)
{
    do
    {
        getline(cin, name);
        size_t j{0};
        for (; name[j] != '\0'; j++)
        {
            if (!((name[j] >= 'a' && name[j] <= 'z') || (name[j] >= 'A' && name[j] <= 'Z') || (name[j] == ' ') || (name[j] == '.')))
                break;
        }
        if (j < name.length())
        {
            cout << "Invalid Input! Re-Enter!" << endl;
            continue;
        }
        break;
    } while (true);
}

void insert(employee &emp)
{
    employee_list *new_employee = new employee_list;
    copy(new_employee->data, emp);
    if (!start)
    {
        start = new_employee;
        start->next = nullptr;
    }
    else
    { // adds element to the end of the list
        employee_list *current = start;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_employee;
        new_employee->next = nullptr;
    }
    list_len++;
}

void add_in_file(employee &emp)
{
    ofstream fout;
    fout.open(FILE_NAME, ios::app | ios::out);
    fout << endl
         << emp.employee_no << "," << emp.name << "," << emp.father_name << "," << date_to_str(emp.date_of_joining) << "," << emp.department << "," << date_to_str(emp.date_of_retirement) << "," << address_to_str(emp.add);
    fout.close();
}

void read_file()
{
    FILE *fin;
    fin = fopen("data.bin", "r");
    if (!fin)
    {
        cout << "Error in Opening the records file!" << endl;
        exit(1);
    }
    employee_list *current{start};
    if (current)
    {
        while (current)
        {
            current = current->next;
        }
    }
    while (feof(fin))
    {
        employee_list *new_employee = new employee_list;
        fscanf(fin, EMPLOYEE_FORMAT_OUT, &new_employee->data.employee_no, &new_employee->data.name, &new_employee->data.father_name, &new_employee->data.department, &new_employee->data.date_of_joining->day, &new_employee->data.date_of_joining->month, &new_employee->data.date_of_joining->year, &new_employee->data.date_of_retirement->day, &new_employee->data.date_of_retirement->month, &new_employee->data.date_of_retirement->year, &new_employee->data.add->house_no, &new_employee->data.add->village, &new_employee->data.add->town, &new_employee->data.add->city, &new_employee->data.add->state, &new_employee->data.add->PIN, &new_employee->data.add->country);
        if (new_employee->data.employee_no == 0)
        {
            delete new_employee;
            break;
        }
        show(new_employee->data);
        if (!current)
        {
            current = new_employee;
        }
        current->next = new_employee;
        current = current->next;
    }
    getch();
    fclose(fin);
}

void write_all_in_file()
{
    FILE *fout;
    fout = fopen("data.bin", "w");
    if (!start)
        return;
    employee_list *current = start;
    while (current)
    {
        fprintf(fout, EMPLOYEE_FORMAT_OUT, current->data.employee_no, current->data.name, current->data.father_name, current->data.department, current->data.date_of_joining->day, current->data.date_of_joining->month, current->data.date_of_joining->year, current->data.date_of_retirement->day, current->data.date_of_retirement->month, current->data.date_of_retirement->year, current->data.add->house_no, current->data.add->village, current->data.add->town, current->data.add->city, current->data.add->state, current->data.add->PIN, current->data.add->country);
        current = current->next;
    }
    fclose(fout);
}