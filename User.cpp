//
// Created by Testa on 5/25/2024.
//

#include "User.h"

void User::addBankAccount(const string& iban, const float balance) {
    map<time_t, Transaction> transactions;
    BankAccount newAccount(iban, balance, transactions);
    bankAccounts.emplace(iban, newAccount);
}

void User::printUser() const {
    cout << name << endl;
    for(const auto& i : bankAccounts) i.second.printBankAccount();
}

bool User::deleteBankAccount(const string &iban) {
    return bankAccounts.erase(iban);
}
