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
    ProgramManager() { users = fileHandler.loadData(); }

    map<string, User> getUsers() const { return users; }
    User getUser(const string& name) { return users[name]; }

    // main methods
    void addUser(const string& name);
    bool addBankAccount(const string& name, const string& iban);
    bool addTransaction(const string& name, const string& iban, char o, float a, time_t t);
    bool addTransaction(const string& name, const string& iban, char o, const string& u, float a, time_t t);

    bool deleteUser(const string& name);
    bool deleteBankAccount(const string& name, const string& iban);
    bool saveData();
    void printUsers() const;

    // auxiliary methods
    bool findUser(const string& n);
    string findRecipientBankAccount(const string& i);

private:
    FileHandler fileHandler;
    map<string, User> users;
};


#endif //BANK_ACCOUNT_PROGRAMMANAGER_H
