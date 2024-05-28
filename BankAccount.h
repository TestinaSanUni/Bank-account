//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_BANKACCOUNT_H
#define BANK_ACCOUNT_BANKACCOUNT_H
#include <string>
#include <list>
#include "Transaction.h"
using namespace std;

class BankAccount {
public:
    BankAccount() = default;
    BankAccount(const string& i, float b) : iban(i), balance(b) {}

    void addTransaction(char o, float a, const string& s, const string& r = "");
    void printBankAccount();

private:
    string iban;
    float balance;
    list<Transaction> transactions;
};


#endif //BANK_ACCOUNT_BANKACCOUNT_H
