//
// Created by Testa on 5/25/2024.
//

#include "BankAccount.h"

list<time_t> BankAccount::getTransactions() const {
    list<time_t> l;

    for(const auto& i : transactions)
        l.push_back(i.first);

    return l;
}

int BankAccount::addTransaction(time_t t, int o, float a) {
    Transaction newTransaction;

    if(t == 0) newTransaction = Transaction(std::time(&t), o, a);
    else newTransaction = Transaction(t, o, a);

    if(o == 2) {
        if (a < 0) a *= -1;
        if (balance >= a) balance -= a;
        else return 5; // insufficient balance
    } else balance += a;

    transactions.emplace(t, newTransaction);
    return 0;
}

int BankAccount::addTransaction(time_t t, int o, float a, const std::string &u, bool r) {
    if(name == u) return 7; // sender and recipient are the same

    Transaction newTransaction;

    if(t == 0) newTransaction = Transaction(std::time(&t), o, a, u, r);
    else newTransaction = Transaction(t, o, a, u, r);

    if(r) {
        if (a < 0) a *= -1;
        if (balance >= a) balance -= a;
        else return 5; // insufficient balance
    } else balance += a;

    transactions.emplace(t, newTransaction);
    return 0;
}

void BankAccount::printAccount() const {
    int counter = 1;
    cout << "\t" << name << " - $" << balance << endl;

    for(const auto& i : transactions) {
        i.second.printTransaction();
        cout << "[#" << counter << "]" << endl;
        counter++;
    }

    cout << endl;
}

int BankAccount::editTransaction(int id, int o, float a) {
    Transaction t = getTransactionById(id);
    if(t.getTrTime() == 0) return 10; // transaction not found

    transactions[t.getTrTime()].setOperation(o);
    transactions[t.getTrTime()].setAmount(a);

    return 0;
}

int BankAccount::editTransaction(int id, int o, float a, const std::string &u, bool r) {
    Transaction t = getTransactionById(id);
    if(t.getTrTime() == 0) return 10; // transaction not found
    if(name == u) return 7; // sender and recipient are the same

    transactions[t.getTrTime()].setOperation(o);
    transactions[t.getTrTime()].setAmount(a);
    transactions[t.getTrTime()].setRecipient(u);
    transactions[t.getTrTime()].setRole(r);

    return 0;
}

int BankAccount::deleteTransaction(int id) {
    Transaction t = getTransactionById(id);
    if(t.getTrTime() == 0) return 10; // transaction not found
    return !transactions.erase(t.getTrTime());
}

void BankAccount::clearTransactions() {
    transactions.clear();
}

Transaction BankAccount::getTransactionById(int id) const {
    if(id > transactions.size()) return {};

    auto i = transactions.begin();
    for(int j = 1; j < id; j++) i++;

    return i->second;
}
