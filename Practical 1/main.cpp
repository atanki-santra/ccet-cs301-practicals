#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "student.h"
using namespace std;
int main()
{
    bool flag {true};
    Student* students = new Student();
    do{
        system("CLS");
        cout << "Student Record Program\n"<< endl;
        cout << "Menu: \n1.Display all records\n2.Add a record\n3.Update a record\n4.Delete a record\n5.Generate Report\n6.Exit" << endl;
        switch (getch()){
            case 49:{//display all records
                system("CLS");
                students->display();
                cout<<"\nPress any key to go to the Main Menu....."<<endl;
                getch();
            }
            break;
            case 50:{//input
                system("CLS");
                cout<<"INPUT WINDOW:\n\n"<<endl;
                students->input();
                cout<<"\nRecord added successfully! Press any key to go to the Main Menu....."<<endl;
                getch();
            }
            break;
            case 51:{//Update
                system("CLS");
                cout<<"UPDATION WINDOW:\n\n"<<endl;
                students->update();
                cout<<"\nRecord updated successfully! Press any key to go to the Main Menu....."<<endl;
                getch();
            }
            break;
            case 52:{//Delete
                system("CLS");
                cout<<"DELETION WINDOW:\n\n"<<endl;
                students->remove();
                cout<<"\nRecord deleted successfully! Press any key to go to the Main Menu....."<<endl;
                getch();
            }
            break;
            case 53:{//Delete
                system("CLS");
                cout<<"REPORT GENERATION:\n\n"<<endl;
                students->generate_report();
                cout<<"\nPress any key to go to the Main Menu....."<<endl;
                getch();
            }
            break;
            case 54://exit
                flag = false;
            break;
        }       
    }while (flag);
    return 0;
}