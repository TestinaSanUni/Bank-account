#include <iostream>
#include <string>
#include <list>
#include "FileHandler.h"
using namespace std;

int main() {
    FileHandler fileHandler;
    list<User> users = fileHandler.loadData();

    for(const User& i : users) i.printUser();

//    list<User> tempUsers;
//    list<BankAccount> tempBankAccounts;
//    list<Transaction> tempTransactions;
//
//    Transaction tempTransaction('D', 100, time(nullptr));
//    tempTransactions.push_back(tempTransaction);
//    tempTransactions.push_back(tempTransaction);
//    BankAccount tempBankAccount("IT69J0300203280263797959377", 100, tempTransactions);
//    tempBankAccounts.push_back(tempBankAccount);
//    tempBankAccounts.push_back(tempBankAccount);
//    User tempUser("Matteo", "Orlandi", tempBankAccounts);
//    tempUsers.push_back(tempUser);
//    tempUsers.push_back(tempUser);
//
//    for(const User& i : tempUsers) i.printUser();

//    fileHandler.saveData(users);
//
//    int choice;
//
//    do {
//        cout << "1) Create new User;" << endl;
//        cout << "2) Create new Bank account;" << endl;
//        cout << "3) Request new transaction;" << endl;
//        cout << "4) Edit User;" << endl;
//        cout << "5) Print Users;" << endl;
//        cout << "6) Print Bank bankAccounts;" << endl;
//        cout << "7) Print Transactions;" << endl;
//        cout << "8) Delete User;" << endl;
//        cout << "9) Delete Bank account;" << endl;
//        cout << "0) Quit the program;" << endl;
//
//        do {
//            cout << "Operation required: " << endl;
//            cin >> choice;
//        } while(choice < 0 || choice > 9);
//
//        switch (choice) {
//            case 1:
//
//                break;
//
//            case 2:
//                break;
//
//            case 3:
//                break;
//
//            case 4:
//                break;
//
//            case 5:
//                break;
//
//            case 6:
//                break;
//
//            case 7:
//                break;
//
//            case 8:
//                break;
//
//            case 9:
//                break;
//
//            default:
//                break;
//        }
//    } while(!choice);

    return 0;
}
