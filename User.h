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
    User() = default;
    explicit User(const string& n) : name(n) {}
    User(const string& n, const map<string, BankAccount>& b) : name(n), bankAccounts(b) {}

    string getName() const { return name; }
    BankAccount getBankAccount(const string& iban) { return bankAccounts[iban]; }
    map<string, BankAccount> getBankAccounts() const { return bankAccounts; }
    void setName(const string& n) { name = n; }

    // main methods
    void addBankAccount(const string& iban);
    bool addTransaction(const string& iban, char o, float a, time_t t);
    bool addTransaction(const string& iban, char o, const string& u, bool r, float a, time_t t);

    bool deleteBankAccount(const string& iban);
    void printUser() const;

    // auxiliary methods
    bool findBankAccount(const string& iban) const;

private:
    string name;
    map<string, BankAccount> bankAccounts;
};


#endif //BANK_ACCOUNT_USER_H
