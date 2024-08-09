#include <iostream>
#include "ProgramManager.h"
using namespace std;

int main() {
    ProgramManager pM;

    int choice;

    do {
        cout << endl << endl << " ===== OPERATIONS =====" << endl;
        cout << "1) Create new User;" << endl;
        cout << "2) Create new Bank account;" << endl;
        cout << "3) Request new transaction;" << endl;
        cout << "4) Edit User;" << endl;
        cout << "5) Print data;" << endl;
        cout << "6) Delete User;" << endl;
        cout << "7) Delete Bank account;" << endl;
        cout << "8) Exit and save;" << endl;
        cout << "0) Exit without saving;" << endl;

        do {
            cout << "Operation required: " << endl;
            cin >> choice;
        } while(choice < 0 || choice > 8);

        cout << endl;

        string name, surname, iban, operation, recipient;
        float amount;
        time_t trTime;

        switch (choice) {
            case 1:
                // add new user
                cout << "Enter your name:";
                cin >> name;
                cout << "Enter your surname:";
                cin >> surname;

                if(pM.addUser(name + " " + surname))
                    cout << "User added successfully" << endl;
                else
                    cout << "This name " << name + " " + surname << " has already been used" << endl;

                break;

            case 2:
                // add new bank account
                cout << "Enter your name:";
                cin >> name;
                cout << "Enter your surname:";
                cin >> surname;
                cout << "Enter the iban:";
                cin >> iban;

                if(pM.addBankAccount(name + " " + surname, iban))
                    cout << "Bank Account added successfully" << endl;
                else
                    cout << "User not found or iban already existing" << endl;

                break;

            case 3:
                // add new transaction
                cout << "Enter your name:";
                cin >> name;
                cout << "Enter your surname:";
                cin >> surname;
                name += " " + surname;

                cout << "Enter one of your Bank Accounts' iban:";
                cin >> iban;

                do {
                    cout << "Enter the operation type (deposit: D, withdrawal: W, bank transfert: B):";
                    cin >> operation;
                } while(operation != "B" && operation != "W" && operation != "D");

                if(operation == "B") {
                    cout << "Enter recipient's iban:";
                    cin >> recipient;

                    cout << "Enter the amount:";
                    cin >> amount;

                    if(pM.addTransaction(name, iban, operation[0], recipient, amount, std::time(&trTime))) {
                        cout << "Transaction added successfully" << endl;
                        cout << "Your new balance is: " << pM.getUser(name).getBankAccount(iban).getBalance() << endl;
                    } else
                        cout << "Something went wrong" << endl;
                } else {
                    cout << "Enter the amount:" << endl;
                    cin >> amount;

                    if(pM.addTransaction(name, iban, operation[0], amount, std::time(&trTime))) {
                        cout << "Transaction added successfully" << endl;
                        cout << "Your new balance is: " << pM.getUser(name).getBankAccount(iban).getBalance() << endl;
                    } else {
                        cout << "Something went wrong" << endl;
                    }
                }

                break;

            case 4:
                // edit user
                cout << "Enter old name:";
                cin >> operation; // random free variable
                cout << "Enter old surname:";
                cin >> recipient; // random free variable
                cout << "Enter new name:";
                cin >> name;
                cout << "Enter new surname:";
                cin >> surname;

                if(pM.setUserName(operation + " " + recipient, name + " " + surname))
                    cout << "Name changed successfully" << endl;
                else
                    cout << "User not found or name not available" << endl;

                break;

            case 5:
                // print
                pM.printUsers();

                break;

            case 6:
                // delete user
                cout << "Enter the name of the user you want to delete:";
                cin >> name;
                cout << "Enter the surname of the user you want to delete:";
                cin >> surname;

                if(pM.deleteUser(name + " " + surname))
                    cout << "User delete successfully" << endl;
                else
                    cout << "User not found" << endl;

                break;

            case 7:
                // delete bank account
                cout << "Enter the name of the user you want to delete:";
                cin >> name;
                cout << "Enter the surname of the user you want to delete:";
                cin >> surname;
                cout << "Enter the iban of the account:";
                cin >> iban;

                if(pM.deleteBankAccount(name + " " + surname, iban))
                    cout << "Bank account deleted successfully" << endl;
                else
                    cout << "User or Bank account not found" << endl;

                break;

            case 8:
                // save and exit
                if(pM.saveData())
                    cout << "Data saved successfully" << endl;
                else
                    cout << "Something went wrong with saving data" << endl;

                break;

            default:
                // exit without saving
                cout << "Data has not been saved" << endl;

                break;
        }
    } while(choice != 0 && choice != 8);

    return 0;
}
