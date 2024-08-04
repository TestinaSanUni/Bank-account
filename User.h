//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_USER_H
#define BANK_ACCOUNT_USER_H
#include <string>
#include <map>
#include "BankAccount.h"
using namespace std;

class User {
public:
    User(const string& n, const map<string, BankAccount>& b) : name(n), bankAccounts(b) {}
    string getName() const { return name; }
    void setName(const string& n) { name = n; }

    void addBankAccount(const string& iban, float balance = 1000);
    void printUser() const;
    bool deleteBankAccount(const string& iban);

private:
    string name;
    map<string, BankAccount> bankAccounts;
};


#endif //BANK_ACCOUNT_USER_H
