#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "functions.h"
using namespace std;

int main()
{
    read_file();
    bool flag{true};
    do
    {
        system("CLS");
        cout << "AUTOMOBILE INVENTORY MANAGEMENT:" << endl
             << endl;
        cout << "Main Menu : " << endl
             << "1. Add a Record" << endl
             << "2. Delete a Record " << endl
             << "3. Count of the parts in the Inventory" << endl
             << "4. List of the expired part" << endl
             << "5. Generate the Report" << endl
             << "6. Display all Records" << endl
             << "7. EXIT" << endl;
        switch (getch())
        {
            case '1':
            {
                system("CLS");
                cout << "INPUT WINDOW:\n"
                    << endl;
                add();
                cout << "\nPress any key to continue...." << endl;
                getch();
            }
            break;
            case '2':
            {
                system("CLS");
                cout << "\n\nDELETION WINDOW:"
                    << endl;
                delete_record();
                cout << "\nPress any key to continue...." << endl;
                getch();
            }
            break;
            case '3':
            {
                cout << "\n\nCOUNT OF PARTS IN THE INVENTORY : " << count();
                cout << "\nPress any key to continue...." << endl;
                getch();
            }
            break;
            case '4':
            {
                system("CLS");
                cout << "LIST OF EXPIRED PARTS:\n"
                    << endl;
                list_of_expired_parts();
                cout << "\nPress any key to continue...." << endl;
                getch();
            }
            break;
            case '5':
            {
                system("CLS");
                cout << "GENERATION OF REPORTS:\n"
                    << endl;
                report();
                cout << "\nPress any key to continue...." << endl;
                getch();
            }
            break;
            case '6':
            {
                system("CLS");
                cout << "THE INVENTORY:\n"
                    << endl;
                display();
                cout << "\nPress any key to continue...." << endl;
                getch();
            }
            break;
            case '7':
                flag = false;
            break;
        }
    } while (flag);
}