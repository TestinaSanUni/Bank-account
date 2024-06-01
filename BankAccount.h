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
    BankAccount(const string& i, float b, const list<Transaction>& t) : iban(i), balance(b), transactions(t) {}
    string getIban() const { return iban; }

    void addTransaction(char o, float a, const string& r);
    void printBankAccount() const;

private:
    string iban;
    float balance;
    list<Transaction> transactions;
};


#endif //BANK_ACCOUNT_BANKACCOUNT_H
