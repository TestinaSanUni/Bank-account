//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_BANKACCOUNT_H
#define BANK_ACCOUNT_BANKACCOUNT_H
#include <string>
#include <map>
#include "Transaction.h"
using namespace std;

class BankAccount {
public:
    explicit BankAccount(float b = 0) : balance(b) {};
    explicit BankAccount(const string& i, float b = 0) : iban(i), balance(b) {}
    BankAccount(const string& i, float b, const map<time_t, Transaction>& t) : iban(i), balance(b), transactions(t) {}

    string getIban() const { return iban; }
    float getBalance() const { return balance; }
    map<time_t , Transaction> getTransactions() const { return transactions; }
    Transaction getTransaction(const time_t& t) { return transactions[t]; }

    void setIban(const string& i) { iban = i; }
    void setBalance(float b) { balance = b; }

    bool addTransaction(char o, float a, time_t t);
    bool addTransaction(char o, const string& u, bool r, float a, time_t t);
    void printBankAccount() const;

private:
    string iban;
    float balance;
    map<time_t , Transaction> transactions;
};


#endif //BANK_ACCOUNT_BANKACCOUNT_H
