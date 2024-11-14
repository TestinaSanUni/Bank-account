//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_USER_H
#define BANK_ACCOUNT_USER_H
#include <string>
#include "BankAccount.h"
using namespace std;

class User {
public:
    // basic methods
    explicit User(const string& n = "") : name(n) {}
    User(const string& n, const map<string, BankAccount>& b) : name(n), accounts(b) {}

    string getName() const { return name; }
    BankAccount getAccount(const string& account) { return accounts[account]; }
    list<string> getAccounts() const;
    void setName(const string& n) { name = n; }

    // main methods
    int addAccount(const string& account);
    int addTransaction(const string& account, time_t t, int o, float a);
    int addTransaction(const string& account, time_t t, int o, float a, const string& u, bool r);

    void printUser() const;
    int searchAccount(const string& account) const;
    int editAccount(const string& oldName, const string& newName);
    int editTransaction(const string& account, int id, int o, float a);
    int editTransaction(const string& account, int id, int o, float a, const string& u, bool r);

    int deleteAccount(const string& account);
    int deleteTransaction(const string& account, int id);
    void clearTransactions(const string& account);
    void clearTransactions();

    // auxiliary methods
    bool findAccount(const string &account) const;

private:
    string name;
    map<string, BankAccount> accounts;
};


#endif //BANK_ACCOUNT_USER_H
