#include "functions.h"

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
         << "6. Exit" << endl;
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

bool check_date_of_joining(date &input, date &today)
{
    if (today.year < input.year)
        return false;
    if (today.year == input.year && today.month < input.month)
        return false;
    if (today.year == input.year && today.month == input.month && today.day <= input.day)
        return false;
    return true;
}

bool check_date_of_retirement(date &input, date &doj)
{
    if (doj.year > input.year)
        return false;
    if (doj.year == input.year && doj.month > input.month)
        return false;
    if (doj.year == input.year && doj.month == input.month && doj.day > input.day)
        return false;
    return true;
}

void get_date(date &out_date, auto date_condition, date &com_date)
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

void input_address(address &a)
{
    cout << "House Number :";
    getline(cin, a.house_no);
    cout << "Village/Town/Street :";
    getline(cin, a.village);
    cout << "Post Office/Town/Circle :";
    getline(cin, a.town);
    cout << "City :";
    get_name(a.city);
    cout << "State :";
    get_name(a.state);
    cout << "PIN :";
    {
        do
        {
            string temp;
            get_number(temp);
            a.PIN = stoi(temp);
            if (a.PIN > 999999 && a.PIN < 100000)
                continue;
            break;
        } while (true);
    }
    cout << "Country :";
    get_name(a.country);
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
        get_date(e.date_of_joining, check_date_of_joining, today);
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
    }
    else
    {
        for (size_t i{0}; i < index; i++)
        {
            current = current->next;
        }
        new_employee->next = current->next;
        current->next = new_employee;
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
                    delete current;
                    cout << "The record has been deleted successfully!" << endl;
                    write_all_in_file();
                    cin.ignore();
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

string date_to_str(date &in_date)
{
    ostringstream oss;
    oss << in_date.day << "/" << in_date.month << "/" << in_date.year;
    return oss.str();
}

string address_to_str(address &add)
{
    ostringstream oss;
    oss << add.house_no << "," << add.village << "," << add.town << "," << add.city << "," << add.state << "," << add.PIN << "," << add.country;
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
                get_date(emp->date_of_joining, check_date_of_joining, today);
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

            delete current;
            current = fwd;
        } while (fwd->next);
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
    write_all_in_file();
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
                if (current->data.add.city == city && current->data.add.state == state && current->data.add.country == country)
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
                if (current->data.date_of_retirement.day == in_date.day && current->data.date_of_retirement.month == in_date.month && current->data.date_of_retirement.year == in_date.year)
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
                if (current->data.date_of_joining.day == in_date.day && current->data.date_of_joining.month == in_date.month && current->data.date_of_joining.year == in_date.year)
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

void insert(employee &emp)
{
    employee_list *new_employee = new employee_list;
    new_employee->data = emp;
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

void write_all_in_file()
{
    ofstream fout;
    fout.open(FILE_NAME);
    if (!fout)
    {
        cout << "Error in Opening the records file!" << endl;
        exit(1);
    }
    if (start == nullptr)
        return;
    employee_list *current = start;
    backup *bckp;
    while (current)
    {
        bckp = bckp_struct(current->data);
        fout.write((char *)&(*bckp), sizeof(*bckp));
        delete bckp;
        current = current->next;
    }
    fout.close();
}

void read_file()
{
    ifstream fin;
    fin.open(FILE_NAME);
    if (!fin)
    {
        cout << "Error in Opening the records file!" << endl;
        exit(1);
    }
    backup bckp;
    employee *emp;
    size_t last{0};
    while (!fin.eof())
    {
        fin.read((char *)(&bckp), sizeof(bckp));
        if(last == bckp.employee_no)
            break;
        emp = (load_struct(bckp));
        insert(*emp);
        last = emp->employee_no;
        delete emp;
    }
    fin.close();
}

backup *bckp_struct(employee &emp)
{
    backup *bkp = new backup();
    bkp->employee_no = emp.employee_no;
    strcpy(bkp->department, emp.department.c_str());
    strcpy(bkp->name, emp.name.c_str());
    strcpy(bkp->father_name, emp.father_name.c_str());
    bkp->date_of_joining = emp.date_of_joining;
    bkp->date_of_retirement = emp.date_of_retirement;
    bkp->add = emp.add;
    return bkp;
}

employee *load_struct(backup &bkp)
{
    employee *emp = new employee();
    emp->employee_no = bkp.employee_no;
    emp->name = bkp.name;
    emp->father_name = bkp.father_name;
    emp->department = bkp.department;
    emp->date_of_joining = bkp.date_of_joining;
    emp->date_of_retirement = bkp.date_of_retirement;
    emp->add = bkp.add;
    return emp;
}
