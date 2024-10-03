//
// Created by Testa on 5/25/2024.
//

#include "User.h"

// ======================================================================================
//      MAIN METHODS
// ======================================================================================

void User::addBankAccount(const string& iban) {
    map<time_t, Transaction> transactions;
    BankAccount newAccount(iban, 0, transactions);
    bankAccounts.emplace(iban, newAccount);
}

int User::addTransaction(const std::string &iban, char o, float a, time_t t) {
    if(!findBankAccount(iban)) return 2; // account not found

    return bankAccounts[iban].addTransaction(o, a, t);
}

int User::addTransaction(const std::string &iban, char o, const std::string &u, bool r, float a, time_t t) {
    if(!findBankAccount(iban)) return 2; // account not found

    return bankAccounts[iban].addTransaction(o, u, r, a, t);
}

// ======================================================================================

void User::printUser() const {
    cout << endl << name << endl << endl;
    for(const auto& i : bankAccounts)
        i.second.printBankAccount();
}

void User::clearTransactions() {
    for(auto& i : bankAccounts)
        i.second.clearTransactions();
}

void User::clearTransactions(const std::string &iban) {
    if(findBankAccount(iban))
        bankAccounts[iban].clearTransactions();
}

int User::deleteBankAccount(const string &iban) {
    if(!findBankAccount(iban)) return 2; // bank account not found
    return !bankAccounts.erase(iban); // return 0 if deleted successfully
}


// ======================================================================================
//      AUXILIARY METHODS
// ======================================================================================

bool User::findBankAccount(const std::string &iban) const {
    return bankAccounts.find(iban) != bankAccounts.end();
}
