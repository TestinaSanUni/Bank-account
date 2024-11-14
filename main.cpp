#include <iostream>
#include "ProgramManager.h"
using namespace std;

void printError(int val);

int main() {

    // TODO FileHandler: scoprire perché non può essere passato da un metodo all'altro

    ProgramManager pM;

    int choice, result;

    do {
        cout << endl << endl << " ===== OPERATIONS =====" << endl;
        cout << "1) Create new User;" << endl;
        cout << "2) Create new Bank account;" << endl;
        cout << "3) Request new transaction;" << endl;
        cout << "4) Edit User;" << endl;
        cout << "5) Edit Bank account;" << endl;
        cout << "6) Edit Transaction;" << endl;
        cout << "7) Print data;" << endl;
        cout << "8) Print transactions by type;" << endl;
        cout << "9) Print transactions by date;" << endl;
        cout << "10) Search Bank account;" << endl;
        cout << "11) Delete User;" << endl;
        cout << "12) Delete Bank account;" << endl;
        cout << "13) Delete Transaction;" << endl;
        cout << "14) Reset transactions from one Bank account;" << endl;
        cout << "15) Reset transactions;" << endl;
        cout << "16) Exit and save;" << endl;
        cout << "0) Exit without saving;" << endl;

        do {
            cout << "Operation required: ";
            cin >> choice;
        } while(choice < 0 || choice > 16);

        cout << endl;

        string name, surname, account, recipient;
        int operation, role;
        float amount;

        switch(choice) {
            case 1:
                // add new user
                cout << "Enter your name: ";
                cin >> name, cin >> surname;

                result = pM.addUser(name + " " + surname);

                if(!result) cout << endl << "User added successfully" << endl;
                else printError(result);

                break;

            case 2:
                // add new bank account
                cout << "Enter your name: ";
                cin >> name, cin >> surname;
                cout << "Enter the name of the Bank Account: ";
                cin >> account;

                result = pM.addBankAccount(name + " " + surname, account);

                if(!result) cout << endl << "Bank Account added successfully" << endl;
                else printError(result);

                break;

            case 3:
                // add new transaction
                cout << "Enter your name: ";
                cin >> name, cin >> surname;
                name = name + " " + surname;
                cout << "Enter the name of the Bank Account: ";
                cin >> account;
                cout << "Enter the operation (deposit: 1, withdrawal: 2, bank transfert: 3): ";
                cin >> operation;
                cout << "Enter the amount: ";
                cin >> amount;

                if(operation == 3) {
                    cout << "Enter recipient's Bank Account name: ";
                    cin >> recipient;

                    result = pM.addTransaction(name, account, operation, recipient, amount);
                } else {
                    result = pM.addTransaction(name, account, operation, amount);
                }

                if(!result) {
                    cout << endl << "Transaction added successfully" << endl;
                    cout << "Your new balance is: " << pM.getUser(name).getAccount(account).getBalance() << endl;
                } else printError(result);

                break;

            case 4:
                // edit user
                cout << "Enter old name: ";
                cin >> account, cin >> recipient; // random free variable (old name, old surname)
                cout << "Enter new name: ";
                cin >> name, cin >> surname;

                result = pM.editUser(account + " " + recipient, name + " " + surname);

                if(!result) cout << endl << "Name changed successfully" << endl;
                else printError(result);

                break;

            case 5:
                // edit bank account
                cout << "Enter your name: ";
                cin >> name, cin >> surname;
                cout << "Enter old Bank Account: ";
                cin >> account;
                cout << "Enter new Bank Account name: ";
                cin >> recipient; // random free variable (new name)

                result = pM.editAccount(name + " " + surname, account, recipient);

                if(!result) cout << endl << "Account's name changed successfully" << endl;
                else printError(result);

                break;

            case 6:
                // edit transaction
                cout << "Enter your name: ";
                cin >> name, cin >> surname;
                name = name + " " + surname;
                cout << "Enter the Bank Account: ";
                cin >> account;
                cout << "Enter the ID of the Transaction: ";
                cin >> result; // free random variable (date)

                cout << "Enter the operation (deposit: 1, withdrawal: 2, bank transfert: 3): ";
                cin >> operation;
                cout << "Enter the amount: ";
                cin >> amount;

                if(operation == 3) {
                    cout << "Enter recipient's Bank Account name: ";
                    cin >> recipient;
                    cout << "Enter the role (received: 0, sent: 1): ";
                    cin >> role;

                    result = pM.editTransaction(name, account, result, operation, recipient, amount, role);
                } else {
                    result = pM.editTransaction(name, account, result, operation, amount);
                }

                if(!result) cout << "Transaction edited successfully" << endl;
                else printError(result);

                break;

            case 7:
                // print
                pM.printInfo();

                break;

            case 8:
                // print transactions by type
                do {
                    cout << "Enter an operation (deposit: 1, withdrawal: 2, bank transfert: 3): ";
                    cin >> operation;
                } while(operation < 1 || operation > 3);

                ProgramManager::printInfo(pM.getByOp(operation));

                break;

            case 9:
                // print transactions by date
                cout << "Insert a date (dd/mm/yyyy): ";
                cin >> name; // random free variable for date

                ProgramManager::printInfo(pM.getByDate(name));

                break;

            case 10:
                // search bank account
                cout << "Enter your name: ";
                cin >> name, cin >> surname;
                cout << "Enter a part of the Bank Account's name: ";
                cin >> account;

                result = pM.searchAccount(name + " " + surname, account);

                if(result) printError(result);
                break;

            case 11:
                // delete user
                cout << "Enter the name of the user: ";
                cin >> name, cin >> surname;

                result = pM.deleteUser(name + " " + surname);

                if(!result) cout << endl << "User delete successfully" << endl;
                else printError(result);

                break;

            case 12:
                // delete bank account
                cout << "Enter the name of the user: ";
                cin >> name, cin >> surname;
                cout << "Enter the name of the Bank Account: ";
                cin >> account;

                result = pM.deleteAccount(name + " " + surname, account);

                if(!result) cout << endl << "Bank account deleted successfully" << endl;
                else printError(result);

                break;

            case 13:
                // delete transaction
                cout << "Enter the name of the user: ";
                cin >> name, cin >> surname;
                cout << "Enter the Bank Account: ";
                cin >> account;
                cout << "Enter the ID of the Transaction: ";
                cin >> result; // free random variable (ID)

                result = pM.deleteTransaction(name + " " + surname, account, result);

                if(!result) cout << endl << "Transaction deleted successfully" << endl;
                else printError(result);

                break;

            case 14:
                // reset transactions from one Bank account
                cout << "Enter your name: ";
                cin >> name, cin >> surname;
                cout << "Enter the name of the Bank account: ";
                cin >> account;

                pM.clearTransactions(name + " " + surname, account);
                cout << "Transactions cleared successfully" << endl;

                break;

            case 15:
                // reset transactions
                pM.clearTransactions();
                cout << "Transactions cleared successfully" << endl;

                break;

            case 16:
                // save and exit
                if(pM.saveData()) {
                    cout << "You exit the program" << endl;
                    cout << "Data saved successfully" << endl;
                } else
                    cout << "Something went wrong saving data" << endl;

                break;

            default:
                // exit without saving
                cout << "You exit the program" << endl;
                cout << "Data has NOT been saved" << endl;

                break;
        }
    } while(choice != 0 && choice != 16);

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
            break;

        case 8:
            cout << endl << "No transaction found" << endl;
            break;

        case 9:
            cout << endl << "Incorrect data" << endl;
            break;

        case 10:
            cout << endl << "Transaction not found" << endl;

        default:
            cout << endl << "Error" << endl;
    }
}
