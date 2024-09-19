//
// Created by Testa on 5/26/2024.
//

#ifndef BANK_ACCOUNT_FILEHANDLER_H
#define BANK_ACCOUNT_FILEHANDLER_H
#include <fstream>
#include <list>
#include "User.h"
using namespace std;

class FileHandler {
public:
    map<string, User> loadData(); // open the files and load the data structures on memory
    bool saveData(const map<string, User>& users); // update files and release allocated memory

private:
    map<string, BankAccount> loadBankAccounts();
    map<time_t, Transaction> loadTransactions();

    fstream file;
};


#endif //BANK_ACCOUNT_FILEHANDLER_H
