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
    explicit ProgramManager(const map<string, User>& u) : users(u) {}; // used for gtest

    User getUser(const string& user);

    // main methods
    int addUser(const string& name);
    int addBankAccount(const string& user, const string& account);
    int addTransaction(const string& user, const string& account, int o, float a, time_t t = 0);
    int addTransaction(const string& user, const string& account, int o, float a, const string& u, time_t = 0);

    void printInfo() const;
    static void printInfo(const map<string, User>& u) ;
    map<string, User> getByOp(int operation) const; // returns all transactions given an operation
    map<string, User> getByDate(const string& date) const; // returns all transactions given a date
    map<string, User> searchAccount(const string& account) const; // returns all account with a part of the name

    int editUser(const string &oldName, const string &newName);
    int editAccount(const string& user, const string& oldAccount, const string& newAccount);
    int editTransaction(const string& user, const string& account, int id, int o, float a);
    int editTransaction(const string& user, const string& account, int id, int o, float a, const string& u, bool r);

    int deleteUser(const string& user);
    int deleteAccount(const string& user, const string& account);
    int deleteTransaction(const string& user, const string& account, int id);

    void clearTransactions(const string& user, const string& account);
    void clearTransactions();
    bool saveData();

private:
    // auxiliary methods
    bool findUser(const string& user) const;
    string findRecipientByAccount(const string& account);

    FileHandler fileHandler;
    map<string, User> users;
};


#endif //BANK_ACCOUNT_PROGRAMMANAGER_H
