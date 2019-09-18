#include <iostream>
#include "database.h"

using namespace std;

int main()
{
    int todo;
    cout << "Loading from file..." << endl << endl;
    loadfile();

    do{
        cout << "Enter 1 to add a member!\t\t"
             << "Enter 2 to save to file!" << endl
             << "\t\t\tEnter 3 to show members!" << endl
             << "Enter 4 to search by name!\t\t"
             << "Enter 5 to remove a member!" << endl
             << "\t\t\t*Enter 0 to Exit*" << endl;

        cin >> todo;

        if (todo==1){
            createNode();
            cout << "Member added successfully!" << endl <<endl;
        }

        else if(todo==2){
            saveFile();
            cout << "Data Saved Successfully!" << endl;
        }

        else if(todo==3){
            showMem();
            cout << endl << endl;
        }

        else if(todo==4){
            searchMem();
        }

        else if(todo==5){
            removeMem();
        }

        cout <<endl;

    }while(todo);
    cout << "Exiting program, THANK YOU!";
    return 0;
}
