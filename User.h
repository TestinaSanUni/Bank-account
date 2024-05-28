//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_USER_H
#define BANK_ACCOUNT_USER_H
#include <string>
#include <list>
#include "BankAccount.h"
using namespace std;

class User {
public:
    User(const string& n, const string& s) : name(n), surname(s) {}
    string getName() const { return name; }
    string getSurname() const { return surname; }
    void setName(const string& n) { name = n; }
    void setSurname(const string& s) { surname = s; }

    void addBankAccount(const string& iban, float balance = 1000);
    void printUser();
    void deleteBankAccount(const string& iban);

private:
    string name;
    string surname;
    list<BankAccount> accounts;
};


#endif //BANK_ACCOUNT_USER_H
