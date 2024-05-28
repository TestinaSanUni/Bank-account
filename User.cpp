//
// Created by Testa on 5/25/2024.
//

#include "User.h"

void User::addBankAccount(const string& iban, const float balance) {
    BankAccount newAccount(iban, balance);
    accounts.push_back(newAccount);
}

void User::printUser() {
    cout << name << " " << surname << endl;
    for(const BankAccount& i : accounts) i.printBankAccount();
    cout << endl;
}

void User::deleteBankAccount(const string &iban) {
    auto iterator = accounts.begin();
    auto endList = accounts.end();

    while(iterator != endList) {
        if(iterator->getIban() == iban) {
            accounts.erase(iterator);
            iterator = endList;
        } else advance(iterator, 1);
    }
}
