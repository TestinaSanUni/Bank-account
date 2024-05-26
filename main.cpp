#include <iostream>
#include <string>
#include <list>
#include "User.h"
#include "FileHandler.h"
using namespace std;

int main() {
    int choice;

    do {
        cout << "1) Create new User;" << endl;
        cout << "2) Create new Bank account;" << endl;
        cout << "3) Request new transaction;" << endl;
        cout << "4) Edit User;" << endl;
        cout << "5) Print Users;" << endl;
        cout << "6) Print Bank accounts;" << endl;
        cout << "7) Print Transactions;" << endl;
        cout << "8) Delete User;" << endl;
        cout << "9) Delete Bank account;" << endl;
        cout << "0) Quit the program;" << endl;

        do {
            cout << "Operation required: " << endl;
            cin >> choice;
        } while(choice < 0 || choice > 9);

        switch (choice) {
            case 1:

                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break;

            default:
                break;
        }
    } while(!choice);

    return 0;
}
