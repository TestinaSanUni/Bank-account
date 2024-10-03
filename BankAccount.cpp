//
// Created by Testa on 5/25/2024.
//

#include "BankAccount.h"

int BankAccount::addTransaction(char o, float a, time_t t) {
    Transaction newTransaction;
    if(t == 0)
        newTransaction = Transaction(o, a, std::time(&t));
    else
        newTransaction = Transaction(o, a, t);

    if (o == 'W')
        if (balance >= a) balance -= a;
        else return 5; // insufficient balance
    else balance += a;

    transactions.emplace(t, newTransaction);
    return 0;
}

int BankAccount::addTransaction(char o, const std::string &u, bool r, float a, time_t t) {
    Transaction newTransaction;

    if(t == 0)
        newTransaction = Transaction(o, u, r, a, std::time(&t));
    else
        newTransaction = Transaction(o, u, r, a, t);

    if(r) {
        if (balance >= a) balance -= a;
        else return 5; // insufficient balance
    } else balance += a;

    transactions.emplace(t, newTransaction);
    return 0;
}

void BankAccount::printBankAccount() const {
    cout << "\t" << iban << " - $" << balance << endl;
    for(const auto& i : transactions) i.second.printTransaction();
    cout << endl;
}

void BankAccount::clearTransactions() {
    transactions.clear();
}