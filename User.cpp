//
// Created by Testa on 5/25/2024.
//

#include "User.h"

void User::addBankAccount(const string& iban, const float balance) {
    list<Transaction> transactions;
    BankAccount newAccount(iban, balance, transactions);
    bankAccounts.push_back(newAccount);
}

void User::printUser() const {
    cout << name << " " << surname << endl;
    for(const BankAccount& i : bankAccounts) i.printBankAccount();
}

void User::deleteBankAccount(const string &iban) {
    auto iterator = bankAccounts.begin();
    auto endList = bankAccounts.end();

    while(iterator != endList) {
        if(iterator->getIban() == iban) {
            bankAccounts.erase(iterator);
            iterator = endList;
        } else advance(iterator, 1);
    }
}
