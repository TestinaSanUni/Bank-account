//
// Created by Testa on 5/25/2024.
//

#include "BankAccount.h"

void BankAccount::addTransaction(const char op, const float a, const string& r) {
    // TODO: implement method
//    Transaction newTransaction(op, r, a, time(nullptr));
//    transactions.push_back(newTransaction);
}

void BankAccount::printBankAccount() const {
    cout << "\t" << iban << " " << balance << endl;
    for(const Transaction& i : transactions) i.printTransaction();
    cout << endl;
}