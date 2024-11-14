//
// Created by Testa on 5/25/2024.
//

#include "User.h"

list<string> User::getAccounts() const {
    list<string> l;

    for(const auto& i : accounts)
        l.push_back(i.first);

    return l;
}

// ======================================================================================
//      MAIN METHODS
// ======================================================================================

int User::addAccount(const string& account) {
    if(findAccount(account)) return 4; // account already existing

    map<time_t, Transaction> transactions;
    BankAccount newAccount(account, 0, transactions);
    accounts.emplace(account, newAccount);

    return 0;
}

int User::addTransaction(const std::string &account, time_t t, int o, float a) {
    if(!findAccount(account)) return 2; // account not found
    return accounts[account].addTransaction(t, o, a);
}

int User::addTransaction(const std::string &account, time_t t, int o, float a, const std::string &u, bool r) {
    if(!findAccount(account)) return 2; // account not found
    return accounts[account].addTransaction(t, o, a, u, r);
}

// ======================================================================================

void User::printUser() const {
    cout << endl << name << endl << endl;

    for(const auto& i : accounts)
        i.second.printAccount();
}

int User::editAccount(const string &oldName, const string &newName) {
    if(!findAccount(oldName)) return 2; // account not found
    if(findAccount(newName)) return 4; // account already existing

    accounts.emplace(newName, accounts[oldName]);
    deleteAccount(oldName);
    accounts[newName].setName(newName);
    return 0;
}

int User::editTransaction(const std::string &account, int id, int o, float a) {
    if(!findAccount(account)) return 2; // bank account not found
    return accounts[account].editTransaction(id, o, a);
}

int User::editTransaction(const std::string &account, int id, int o, float a, const std::string &u, bool r) {
    if(!findAccount(account)) return 2; // bank account not found
    return accounts[account].editTransaction(id, o, a, u, r);
}

int User::searchAccount(const std::string &account) const {
    bool found = false;

    cout << endl << " ----------------------------------------------------------------------" << endl << endl;
    for(const auto& i : accounts) {
        if(i.first.find(account) != std::string::npos) {
            found = true;
            i.second.printAccount();
        }
    }
    cout << " ----------------------------------------------------------------------" << endl;

    return found ? 0 : 2;
}

int User::deleteAccount(const string &account) {
    if(!findAccount(account)) return 2; // account not found
    return !accounts.erase(account); // return 0 if deleted successfully
}

int User::deleteTransaction(const std::string &account, int id) {
    if(!findAccount(account)) return 2; // account not found
    return accounts[account].deleteTransaction(id);
}

void User::clearTransactions(const std::string &account) {
    if(findAccount(account))
        accounts[account].clearTransactions();
}

void User::clearTransactions() {
    for(auto& i : accounts)
        i.second.clearTransactions();
}


// ======================================================================================
//      AUXILIARY METHODS
// ======================================================================================

bool User::findAccount(const string &account) const {
    return accounts.find(account) != accounts.end();
}
