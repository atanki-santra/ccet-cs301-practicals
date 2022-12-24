#include "functions.h"

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

void input_part_details(part &in_part)
{
    cout << "Enter Part Details :\n"
         << endl;
    do
    {
        cout << "Enter Company ID : ";
        getline(cin, in_part.company_ID);
        cout << "Enter Part ID : ";
        getline(cin, in_part.part_ID);
        if (check_valid_key(in_part.company_ID, in_part.part_ID) != -1)
        {
            cout << "Invalid Key! Re-Enter! : ";
            continue;
        }
        break;
    } while (true);
    cout << "Enter Part Name : ";
    get_name(in_part.name);
    cout << "Enter quantity : ";
    string temp;
    get_number(temp);
    in_part.quantity = stoi(temp);
    cout << "\nEnter manufacturing date : " << endl;
    date today = current_date();
    get_date(in_part.mfg_date, check_date_of_mfg, today);
    cout << "\nEnter expiry date : " << endl;
    get_date(in_part.exp_date, check_date_of_expiry, in_part.mfg_date);
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
                cout << "Invalid Date! Re-Enter : ";
            } while (true);
        }
        if (!date_condition(in_date, com_date))
        {
            cout << "Date is Invalid! Re-Enter!" << endl;
            continue;
        }
        out_date = in_date;
        break;
    } while (true);
    cin.ignore();
}

bool check_date_of_mfg(date &input, date &com_date)
{
    if (com_date.year < input.year)
        return false;
    if (com_date.year == input.year && com_date.month < input.month)
        return false;
    if (com_date.year == input.year && com_date.month == input.month && com_date.day < input.day)
        return false;
    return true;
}

bool check_date_of_expiry(date &input, date &com_date)
{
    if (com_date.year > input.year)
        return false;
    if (com_date.year == input.year && com_date.month > input.month)
        return false;
    if (com_date.year == input.year && com_date.month == input.month && com_date.day > input.day)
        return false;
    return true;
}

bool is_leap_year(const int &year)
{
    if (year % 4 == 0)
    {
        return (year % 100 != 0 || year % 400 == 0);
    }
    return false;
}

int check_valid_key(string &cID, string &pID)
{
    if (!LP)
        return -1;
    node *current = LP;
    int index = 0;
    while (current)
    {
        if ((current->data.company_ID == (cID) && (current->data.part_ID == pID)))
            return index;
        current = current->next;
        index++;
    }
    return -1;
}

void insert()
{
    node *new_part = new node;
    input_part_details(new_part->data);
    node *ptr = RP;
    list_len++;
    if (!RP)
    {
        new_part->prev = nullptr;
        new_part->next = nullptr;
        LP = new_part;
        RP = new_part;
        write_all_in_file();
        return;
    }
    ptr->next = new_part;
    ptr->next->prev = ptr;
    RP = ptr;
    add_in_file(new_part->data);
}

void insert(int &index)
{
    node *new_part = new node;
    input_part_details(new_part->data);
    node *ptr = LP;
    list_len++;
    if (!LP)
    {
        new_part->prev = nullptr;
        new_part->next = nullptr;
        LP = new_part;
        RP = new_part;
        write_all_in_file();
        return;
    }
    if (index == 0)
    {
        new_part->prev = nullptr;
        new_part->next = ptr;
        new_part->next->prev = new_part;
        LP = new_part;
        write_all_in_file();
        return;
    }
    if (index == (list_len - 1))
    {
        ptr = RP;
        new_part->next = nullptr;
        new_part->prev = ptr;
        new_part->prev->next = new_part;
        RP = new_part;
        add_in_file(new_part->data);
        return;
    }
    for (size_t i{0}; i <= index; i++)
        ptr = ptr->next;
    ptr->prev->next = new_part;
    ptr->next->prev = new_part;
    new_part->next = ptr;
    new_part->prev = ptr->prev;
    write_all_in_file();
}

void insert(part &in_part)
{
    node *new_part = new node;
    new_part->data = in_part;
    node *ptr = RP;
    list_len++;
    if (!RP)
    {
        new_part->prev = nullptr;
        new_part->next = nullptr;
        LP = new_part;
        RP = new_part;
        return;
    }
    ptr->next = new_part;
    ptr->next->prev = ptr;
    RP = new_part;
}

size_t count()
{
    node *ptr = LP;
    size_t size{0};
    while (ptr)
    {
        size = size + ptr->data.quantity;
        ptr = ptr->next;
    }
    return size;
}

void add()
{
    int index;
    bool flag{true};
    do
    {
        system("CLS");
        cout << "Enter where you want to insert the record :" << endl
             << "1. At Head" << endl
             << "2. At a desired index" << endl
             << "3. At the tail" << endl
             << "4. Exit" << endl;
        switch (getch())
        {
        case '1':
        {
            index = 0;
            insert(index);
        }
        break;
        case '2':
        {
            cout << "\nEnter the desired index :" << endl;
            do
            {
                string temp;
                get_number(temp);
                index = stoi(temp);
                if (index < 0 || index > list_len)
                {
                    cout << "Invalid INDEX! Re-Enter!" << endl;
                    continue;
                }
                break;
            } while (true);
            insert(index);
        }
        break;
        case '3':
            insert();
            break;
        case '4':
            flag = false;
            break;
        }
    } while (flag);
    merge_sort(LP, 0, list_len - 1);
    write_all_in_file();
}

void remove()
{
    int index;
    cout << "\nEnter the desired index :" << endl;
    do
    {
        string temp;
        get_number(temp);
        index = stoi(temp);
        if (index < 0 || index > list_len - 1)
        {
            cout << "Invalid INDEX! Re-Enter!" << endl;
            continue;
        }
        break;
    } while (true);
    node *ptr;
    list_len--;
    if (index == 0)
    {
        ptr = LP;
        ptr->prev = nullptr;
        ptr = ptr->next;
        delete LP;
        LP = ptr;
        write_all_in_file();
        return;
    }
    if (index == (list_len - 1))
    {
        ptr = RP->prev;
        show(ptr->data);
        cout << "here" << endl;
        ptr->next = nullptr;
        cout << "here" << endl;
        delete RP;
        cout << "here" << endl;
        RP = ptr;
        write_all_in_file();
        return;
    }
    ptr = LP;
    for (size_t i{0}; i < index; i++)
        ptr = ptr->next;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    delete ptr;
    write_all_in_file();
}

void remove(size_t index)
{
    node *ptr;
    if (index == 0)
    {
        ptr = LP;
        ptr->prev = nullptr;
        ptr = ptr->next;
        delete LP;
        LP = ptr;
        write_all_in_file();
        list_len--;
        return;
    }
    if (index == (list_len - 1))
    {
        ptr = RP->prev;
        show(ptr->data);
        cout << "here" << endl;
        ptr->next = nullptr;
        cout << "here" << endl;
        delete RP;
        cout << "here" << endl;
        RP = ptr;
        write_all_in_file();
        list_len--;
        return;
    }
    ptr = LP;
    for (size_t i{0}; i < index; i++)
        ptr = ptr->next;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    delete ptr;
    write_all_in_file();
    list_len--;
}

void display()
{
    node *ptr = LP;
    cout << string(120, '-') << endl;
    cout << setw(10) << left << "Sr.No." << setw(20) << left << "Company ID" << setw(20) << left << "Part ID" << setw(30) << left << "Part Name" << setw(12) << left << "Quantity" << setw(15) << left << "Date of" << setw(15) << left << "Date of" << endl
         << setw(10) << " " << setw(20) << " " << setw(20) << " " << setw(30) << " " << setw(12) << " " << left << setw(15) << "Manufacture" << setw(15) << left << "Expiry" << endl
         << string(120, '-') << endl;
    int srno{0};
    while (ptr)
    {
        srno++;
        show(ptr->data, srno);
        ptr = ptr->next;
    }
    cout << string(120, '-') << endl;
    cout << setw(20) << "Total Records :" << list_len << endl;
}

void show(part &prt)
{
    cout << setw(20) << left << prt.company_ID << setw(20) << prt.part_ID << setw(30) << prt.name << setw(12) << prt.quantity << setw(15) << date_to_str(prt.mfg_date) << setw(15) << date_to_str(prt.exp_date) << endl;
}

void show(part &prt, int srno)
{
    cout << setw(10) << left << srno << setw(20) << left << prt.company_ID << setw(20) << prt.part_ID << setw(30) << prt.name << setw(12) << prt.quantity << setw(15) << date_to_str(prt.mfg_date) << setw(15) << date_to_str(prt.exp_date) << endl;
}

string date_to_str(date &in_date)
{
    ostringstream oss;
    oss << in_date.day << "/" << in_date.month << "/" << in_date.year;
    return oss.str();
}

void list_of_expired_parts()
{
    size_t count{0};
    size_t exp_count{0};
    node *ptr = LP;
    date today = current_date();
    if (!ptr)
    {
        cout << "Empty List !" << endl;
        return;
    }
    cout << string(120, '-') << endl;
    while (ptr)
    {
        if (ptr->data.exp_date.year > today.year)
        {
            ptr = ptr->next;
            continue;
        }
        if (ptr->data.exp_date.year == today.year && ptr->data.exp_date.month > today.month)
        {
            ptr = ptr->next;
            continue;
        }
        if (ptr->data.exp_date.year == today.year && ptr->data.exp_date.month == today.month && ptr->data.exp_date.day > today.day)
        {
            ptr = ptr->next;
            continue;
        }
        show(ptr->data);
        count++;
        exp_count = exp_count + ptr->data.quantity;
        ptr = ptr->next;
    }
    cout << string(120, '-') << endl;
    cout << "Total Records : " << count << endl;
    cout << "Total Expired parts : " << exp_count << endl;
}

backup *backup_struct(part &prt)
{
    backup *bkp = new backup();
    strcpy(bkp->company_ID, prt.company_ID.c_str());
    strcpy(bkp->part_ID, prt.part_ID.c_str());
    strcpy(bkp->name, prt.name.c_str());
    bkp->quantity = prt.quantity;
    bkp->mfg_date = prt.mfg_date;
    bkp->exp_date = prt.exp_date;
    return bkp;
}

part *load_struct(backup &bkp)
{
    part *prt = new part();
    prt->company_ID = bkp.company_ID;
    prt->part_ID = bkp.part_ID;
    prt->name = bkp.name;
    prt->quantity = bkp.quantity;
    prt->mfg_date = bkp.mfg_date;
    prt->exp_date = bkp.exp_date;
    return prt;
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
    if (!LP)
        return;
    node *current = LP;
    backup *bckp;
    while (current)
    {
        bckp = backup_struct(current->data);
        fout.write((char *)&(*bckp), sizeof(*bckp));
        delete bckp;
        current = current->next;
    }
    fout.close();
}

void add_in_file(part &in_part)
{
    ofstream fout;
    fout.open(FILE_NAME, ios::app | ios::out);
    if (!fout)
    {
        cout << "Error in Opening the records file!" << endl;
        exit(1);
    }
    if (LP == nullptr)
        return;
    backup *bckp;
    bckp = backup_struct(in_part);
    fout.write((char *)&(*bckp), sizeof(*bckp));
    delete bckp;
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
    fin.seekg(0, ios::end);
    if (fin.tellg() == 0)
        return;
    fin.seekg(0, ios::beg);
    backup bckp;
    part *prt;
    string last1{""};
    string last2{""};
    while (!fin.eof())
    {
        fin.read((char *)(&bckp), sizeof(bckp));
        if ((last1 == bckp.part_ID && last2 == bckp.company_ID) || bckp.company_ID[0] == '\0')
            break;
        prt = (load_struct(bckp));
        insert(*prt);
        last1 = prt->part_ID;
        last2 = prt->company_ID;
        delete prt;
    }
    fin.close();
}

void merge(node *list, int begin, int mid, int end)
{
    int len_left_sublist = mid - begin + 1;
    int len_right_sublist = end - mid;

    part *left_sublist = new part[len_left_sublist];
    part *right_sublist = new part[len_right_sublist];

    node *current = list;

    for (int i{0}; i < begin; i++)
        current = current->next;
    for (int i{0}; i < len_left_sublist; i++)
    {
        left_sublist[i] = current->data;
        current = current->next;
    }
    for (int i{0}; i < len_right_sublist; i++)
    {
        right_sublist[i] = current->data;
        current = current->next;
    }

    current = list;
    for (int i{0}; i < begin; i++)
        current = current->next;

    int index_left_list = 0, index_right_list = 0, index_merged_list = begin;

    while (index_left_list < len_left_sublist && index_right_list < len_right_sublist)
    {
        if (!check_date_of_mfg(left_sublist[index_left_list].mfg_date, right_sublist[index_right_list].mfg_date)) // first date > second date
        {
            current->data = right_sublist[index_right_list];
            index_right_list++;
        }
        else
        {   
            current->data = left_sublist[index_left_list];
            index_left_list++;
        }
        current = current->next;
    }

    while (index_left_list < len_left_sublist)
    {
        current->data = left_sublist[index_left_list];
        index_left_list++;
        current = current->next;
    }

    while (index_right_list < len_right_sublist)
    {
        current->data = right_sublist[index_right_list];
        index_right_list++;
        current = current->next;
    }

    delete[] left_sublist;
    delete[] right_sublist;
}

void merge_sort(node *list, int begin, int end)
{
    if (begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    merge_sort(list, begin, mid);
    merge_sort(list, mid + 1, end);
    merge(list, begin, mid, end);
}

void delete_record()
{
    int index;
    bool flag{true};
    do
    {
        system("CLS");
        cout << "Enter using what parameter you want to delete the record :" << endl
             << "1. Using Primary Key" << endl
             << "2. At a desired index" << endl
             << "3. Exit" << endl;
        switch (getch())
        {
        case '1':
        {
            do
            {
                string cID, pID;
                cout << "\nEnter Company ID : ";
                getline(cin, cID);
                cout << "Enter Part ID : ";
                getline(cin, pID);
                index = check_valid_key(cID, pID);
                if (index == -1)
                {
                    cout << "Invalid Key! Re-Enter! " << endl;
                    continue;
                }
                remove(index);
                break;
            } while (true);
        }
        break;
        case '2':
            insert();
            break;
        case '3':
            flag = false;
            break;
        }
    } while (flag);
}

void report()
{
    bool flag{true};
    do
    {
        system("CLS");
        cout << "Generate report on the basis of :" << endl
             << "1. Company ID" << endl
             << "2. Part ID" << endl
             << "3. Part Name" << endl
             << "4. Date of Manufacture" << endl
             << "5. Date of Expiry" << endl
             << "6. EXIT" << endl
             << endl;
        switch (getch())
        {
            case '1':
            {
                node *current = LP;
                if (!current)
                {
                    printf("No Records in the Database!");
                    return;
                }
                string cid;
                printf("Enter the Company ID ");
                getline(cin, cid);
                cout << endl
                    << "Generated report : " << endl;
                while (current)
                {
                    if (current->data.company_ID == cid)
                        show(current->data);
                    current = current->next;
                }
                getch();
            }
            break;
            case '2':
            {
                node *current = LP;
                if (!current)
                {
                    printf("No Records in the Database!");
                    return;
                }
                string pid;
                printf("Enter the Part ID ");
                getline(cin, pid);
                cout << endl
                    << "Generated report : " << endl;
                while (current)
                {
                    if (current->data.part_ID == pid)
                        show(current->data);
                    current = current->next;
                }
                getch();
            }
            break;
            case '3':
            {
                node *current = LP;
                if (!current)
                {
                    printf("No Records in the Database!");
                    return;
                }
                string name;
                printf("Enter the Part Name ");
                get_name(name);
                cout << endl
                    << "Generated report : " << endl;
                while (current)
                {
                    if (current->data.name == name)
                        show(current->data);
                    current = current->next;
                }
                getch();
            }
            break;
            case '4':
            {
                node *current = LP;
                if (!current)
                {
                    printf("No Records in the Database!");
                    return;
                }
                date mfg;
                date today = current_date();
                printf("Enter the date of manufacture ");
                get_date(mfg, check_date_of_mfg, today);
                cout << endl
                    << "Generated report : " << endl;
                while (current)
                {
                    if (current->data.mfg_date.day == mfg.day && current->data.mfg_date.month == mfg.month && current->data.mfg_date.year == mfg.year)
                        show(current->data);
                    current = current->next;
                }
                getch();
            }
            break;
            case '5':
            {
                node *current = LP;
                if (!current)
                {
                    printf("No Records in the Database!");
                    return;
                }
                date exp;
                date temp{1, 1, 1900};
                printf("Enter the date of expiry ");
                get_date(exp, check_date_of_expiry, temp);
                cout << endl
                    << "Generated report : " << endl;
                while (current)
                {
                    if (current->data.exp_date.day == exp.day && current->data.exp_date.month == exp.month && current->data.exp_date.year == exp.year)
                        show(current->data);
                    current = current->next;
                }
                getch();
            }
            break;
            case '6':
                flag = false;
        }
    } while (flag);
}