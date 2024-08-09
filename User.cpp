//
// Created by Testa on 5/25/2024.
//

#include "User.h"

//
// main methods
//

void User::addBankAccount(const string& iban) {
    map<time_t, Transaction> transactions;
    BankAccount newAccount(iban, 0, transactions);
    bankAccounts.emplace(iban, newAccount);
}

bool User::addTransaction(const std::string &iban, char o, float a, time_t t) {
    if(findBankAccount(iban))
        return bankAccounts[iban].addTransaction(o, a, t);

    return false;
}

bool User::addTransaction(const std::string &iban, char o, const std::string &u, bool r, float a, time_t t) {
    if(findBankAccount(iban) && iban != u)
        return bankAccounts[iban].addTransaction(o, u, r, a, t);

    return false;
}

void User::printUser() const {
    cout << name << endl;
    for(const auto& i : bankAccounts) i.second.printBankAccount();
}

bool User::deleteBankAccount(const string &iban) {
    return bankAccounts.erase(iban);
}


//
// auxiliary methods
//

bool User::findBankAccount(const std::string &iban) const {
    return bankAccounts.find(iban) != bankAccounts.end();
}
