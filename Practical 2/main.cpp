#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include "functions.h"
#include "structure.h"
using namespace std;

int main()
{
    read_file();
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
        }
    } while (flag);
    write_all_in_file();
    list_destructor();
    return 0;
}