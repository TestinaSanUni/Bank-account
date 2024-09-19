#include <iostream>
#include "ProgramManager.h"
using namespace std;

void printError(int val);

int main() {

    ProgramManager pM;

    int choice, result;

    do {
        cout << endl << endl << " ===== OPERATIONS =====" << endl;
        cout << "1) Create new User;" << endl;
        cout << "2) Create new Bank account;" << endl;
        cout << "3) Request new transaction;" << endl;
        cout << "4) Edit User;" << endl;
        cout << "5) Print data;" << endl;
        cout << "6) Print transactions by type;" << endl;
        cout << "7) Print transactions by date;" << endl;
        cout << "8) Reset transactions;" << endl;
        cout << "9) Reset transactions from one Bank account;" << endl;
        cout << "10) Delete User;" << endl;
        cout << "11) Delete Bank account;" << endl;
        cout << "12) Exit and save;" << endl;
        cout << "0) Exit without saving;" << endl;

        do {
            cout << "Operation required: ";
            cin >> choice;
        } while(choice < 0 || choice > 12);

        cout << endl;

        string name, surname, iban, recipient;
        char operation;
        float amount;

        switch (choice) {
            case 1:
                // add new user
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter your surname: ";
                cin >> surname;

                result = pM.addUser(name + " " + surname);
                if(!result)
                    cout << endl << "User added successfully" << endl;
                else
                    printError(result);

                break;

            case 2:
                // add new bank account
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter your surname: ";
                cin >> surname;
                cout << "Enter the iban: ";
                cin >> iban;

                result = pM.addBankAccount(name + " " + surname, iban);
                if(!result)
                    cout << endl << "Bank Account added successfully" << endl;
                else
                    printError(result);

                break;

            case 3:
                // add new transaction
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter your surname: ";
                cin >> surname;
                name += " " + surname;

                cout << "Enter one of your Bank Accounts' iban: ";
                cin >> iban;

                do {
                    cout << "Enter the operation type (deposit: D, withdrawal: W, bank transfert: B): ";
                    cin >> operation;
                } while(operation != 'B' && operation != 'W' && operation != 'D');

                if(operation == 'B') {
                    cout << "Enter recipient's iban: ";
                    cin >> recipient;

                    cout << "Enter the amount: ";
                    cin >> amount;

                    result = pM.addTransaction(name, iban, operation, recipient, amount);
                    if(!result) {
                        cout << endl << "Transaction added successfully" << endl;
                        cout << "Your new balance is: " << pM.getUser(name).getBankAccount(iban).getBalance() << endl;
                    } else
                        printError(result);
                } else {
                    cout << "Enter the amount: ";
                    cin >> amount;

                    result = pM.addTransaction(name, iban, operation, amount);
                    if(!result) {
                        cout << endl << "Transaction added successfully" << endl;
                        cout << "Your new balance is: " << pM.getUser(name).getBankAccount(iban).getBalance() << endl;
                    } else {
                        printError(result);
                    }
                }

                break;

            case 4:
                // edit user
                cout << "Enter old name: ";
                cin >> iban; // random free variable (old name)
                cout << "Enter old surname: ";
                cin >> recipient; // random free variable (old surname)
                cout << "Enter new name: ";
                cin >> name;
                cout << "Enter new surname: ";
                cin >> surname;

                result = pM.setUserName(iban + " " + recipient, name + " " + surname);
                if(!result)
                    cout << endl << "Name changed successfully" << endl;
                else
                    printError(result);

                break;

            case 5:
                // print
                pM.printInfo();

                break;

            case 6:
                // print transactions by type
                do {
                    cout << "Enter an operation (deposit: D, withdrawal: W, bank transfert: B): ";
                    cin >> operation;
                } while(operation != 'D' && operation != 'W' && operation != 'B');

                pM.printInfo(operation);

                break;

            case 7:
                // print transactions by date
                cout << "Insert a date (dd/mm/yyyy): ";
                cin >> name; // random free variable (date)
                pM.printInfo(name);

                break;

            case 8:
                // reset transactions
                pM.clearTransactions();
                cout << "Transactions cleared successfully" << endl;

                break;

            case 9:
                // reset transactions from one Bank account
                cout << "Enter a user's name: ";
                cin >> name;
                cout << "Enter a user's surname: ";
                cin >> surname;
                cout << "Enter one of the Bank account's iban: ";
                cin >> iban;

                pM.clearTransactions(name + " " + surname, iban);
                cout << "Transactions cleared successfully" << endl;

                break;

            case 10:
                // delete user
                cout << "Enter the name of the user you want to delete: ";
                cin >> name;
                cout << "Enter the surname of the user you want to delete: ";
                cin >> surname;

                result = pM.deleteUser(name + " " + surname);
                if(!result)
                    cout << endl << "User delete successfully" << endl;
                else
                    printError(result);

                break;

            case 11:
                // delete bank account
                cout << "Enter the name of the user you want to delete: ";
                cin >> name;
                cout << "Enter the surname of the user you want to delete: ";
                cin >> surname;
                cout << "Enter the iban of the account: ";
                cin >> iban;

                result = pM.deleteBankAccount(name + " " + surname, iban);
                if(!result)
                    cout << endl << "Bank account deleted successfully" << endl;
                else
                    printError(result);

                break;

            case 12:
                // save and exit
                if(pM.saveData()) {
                    cout << "You exit the program" << endl;
                    cout << "Data saved successfully" << endl;
                } else
                    cout << "Something went wrong with saving data" << endl;

                break;

            default:
                // exit without saving
                cout << "You exit the program" << endl;
                cout << "Data has NOT been saved" << endl;

                break;
        }
    } while(choice != 0 && choice != 12);

    return 0;
}

void printError(int val) {
    switch (val) {
        case 1:
            cout << endl << "User not found" << endl;
            break;

        case 2:
            cout << endl << "Bank Account not found" << endl;
            break;

        case 3:
            cout << endl << "User already existing" << endl;
            break;

        case 4:
            cout << endl << "Bank Account already existing" << endl;
            break;

        case 5:
            cout << endl << "Insufficient balance" << endl;
            break;

        case 6:
            cout << endl << "Recipient account not found" << endl;
            break;

        case 7:
            cout << endl << "Sender and recipient are the same" << endl;
    }
}
