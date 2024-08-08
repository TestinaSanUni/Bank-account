//
// Created by Testa on 5/25/2024.
//

#include "BankAccount.h"

bool BankAccount::addTransaction(char o, float a, time_t t) {
    Transaction newTransaction(o, a, t);

    if(o == 'W')
        if(balance >= a) balance -= a;
        else return false;
    else balance += a;

    transactions.emplace(t, newTransaction);
    printBankAccount();
    return true;
}

bool BankAccount::addTransaction(char o, const std::string &u, bool r, float a, time_t t) {
    Transaction newTransaction(o, u, r, a, t);
    if(r)
        if(balance >= a) balance -= a;
        else return false;
    else balance += a;

    transactions.emplace(t, newTransaction);
    return true;
}

void BankAccount::printBankAccount() const {
    cout << "\t" << iban << " " << balance << endl;
    for(const auto& i : transactions) i.second.printTransaction();
    cout << endl;
}