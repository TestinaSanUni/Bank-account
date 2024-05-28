//
// Created by Testa on 5/25/2024.
//

#include "BankAccount.h"

void BankAccount::addTransaction(const char o, const float a, const string& s, const string& r) {
    Transaction newTransaction(o, a, s, r);
    transactions.push_back(newTransaction);
}

void BankAccount::printBankAccount() const {
    cout << "\t" << iban << " " << balance << endl;
    for(const Transaction& i : transactions) i.printTransaction();
    cout << endl;
}