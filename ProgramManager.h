//
// Created by irene on 08/08/2024.
//

#ifndef BANK_ACCOUNT_PROGRAMMANAGER_H
#define BANK_ACCOUNT_PROGRAMMANAGER_H

#include "User.h"
#include "FileHandler.h"

class ProgramManager {
public:
    // basic methods
    ProgramManager() { users = fileHandler.loadData("Data.txt"); }

    map<string, User> getUsers() const { return users; }
    User getUser(const string& name) { return users[name]; }
    int setUserName(const string& oldName, const string& newName);

    // main methods
    int addUser(const string& name);
    int addBankAccount(const string& name, const string& iban);
    int addTransaction(const string& name, const string& iban, char o, float a, time_t t = 0);
    int addTransaction(const string& name, const string& iban, char o, const string& u, float a, time_t = 0);

    void printInfo() const;
    int printInfo(char operation); // prints all transactions given an operation
    int printInfo(string date); // prints all transactions given a date

    void clearTransactions();
    void clearTransactions(const string& name, const string& iban);

    int deleteUser(const string& name);
    int deleteBankAccount(const string& name, const string& iban);
    bool saveData();

private:
    // auxiliary methods
    bool findUser(const string& name) const;
    string findRecipientBankAccount(const string& iban);
    bool checkAllIban(const string& iban);
    string formatData(time_t time);
    bool checkData(const string& date);

    FileHandler fileHandler;
    map<string, User> users;
};


#endif //BANK_ACCOUNT_PROGRAMMANAGER_H
