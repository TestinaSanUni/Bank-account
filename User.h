//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_USER_H
#define BANK_ACCOUNT_USER_H
#include <fstream>
#include <string>
#include <list>
#include "BankAccount.h"
using namespace std;


class User {
public:
    User() = default;
    User(const string& n, const string& s) : name(n), surname(s) {}
    BankAccount getBankAccount(const string& iban); // get a specific bank account
    string getName() const { return name; } // get user's name
    string getSurname() const { return surname; } // get user's surname
    void setName(const string& n) { name = n; } // change user's name
    void setSurname(const string& s) { surname = s; } // change user's surname

    void addBankAccount(const string& iban, int balance = 1000); // create a new bank account
    void printUser(); // print the user
    void printBankAccounts(); // print every user's bank account
    void deleteBankAccount(const string& iban); // delete a specific bank account

private:
    void loadBankAccounts(); // read and load every user's bank account from memory
    int findBankAccount(const string& iban); // find a specific bank account

    string name;
    string surname;
    list<BankAccount> accounts;
};


#endif //BANK_ACCOUNT_USER_H
