//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_BANKACCOUNT_H
#define BANK_ACCOUNT_BANKACCOUNT_H
#include <string>
#include <map>
#include <list>
#include "Transaction.h"
using namespace std;

class BankAccount {
public:
    // basic methods
    explicit BankAccount(float b = 0) : balance(b) {};
    explicit BankAccount(const string& i, float b = 0) : name(i), balance(b) {}
    BankAccount(const string& i, float b, const map<time_t, Transaction>& t) : name(i), balance(b), transactions(t) {}

    string getName() const { return name; }
    float getBalance() const { return balance; }
    Transaction getTransaction(const time_t& t) { return transactions[t]; }
    list<time_t> getTransactions() const;
    void setName(const string& n) { name = n; }

    // main methods
    int addTransaction(time_t t, int o, float a);
    int addTransaction(time_t t, int o, float a, const string& u, bool r);

    void printAccount() const;
    int editTransaction(int id, int o, float a);
    int editTransaction(int id, int o, float a, const string& u, bool r);

    int deleteTransaction(int id);
    void clearTransactions();

private:
    Transaction getTransactionById(int id) const;

    string name;
    float balance;
    map<time_t , Transaction> transactions;
};


#endif //BANK_ACCOUNT_BANKACCOUNT_H
