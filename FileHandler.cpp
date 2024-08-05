//
// Created by Testa on 5/26/2024.
//

#include "FileHandler.h"
#include <iostream>

map<string, User> FileHandler::loadData() {
    map<string, User> users;
    file.open("Data.txt", ios::in);

    if(file.is_open()) {
        map<string, BankAccount> accounts;
        string name[2];

        while(!file.eof() && file >> name[0] && file >> name[1]) {
            accounts = loadBankAccounts();
            User newUser(name[0] + " " + name[1], accounts);
            users.emplace(name[0] + " " + name[1], newUser);
        }

        file.close();
    }

    return users;
}

map<string, BankAccount> FileHandler::loadBankAccounts() {
    map<string, BankAccount> accounts;
    map<time_t, Transaction> transactions;
    string iban;
    float balance;

    while(file >> iban && iban != "end_accounts" && file >> balance) {
        transactions = loadTransactions(iban);
        BankAccount newBankAccount(iban, balance, transactions);
        accounts.emplace(iban, newBankAccount);
    }

    return accounts;
}

map<time_t, Transaction> FileHandler::loadTransactions(const string& author) {
    map<time_t, Transaction> transactions;
    string type, iban;
    bool role;
    float amount;
    time_t trTime;

    while(file >> type && type != "end_transactions") {
        if (type == "B") {
            file >> iban, file >> role, file >> amount, file >> trTime;
            Transaction newTransaction(type[0], iban, role, amount, trTime);
            transactions.emplace(trTime, newTransaction);
        } else {
            file >> amount, file >> trTime;
            Transaction newTransaction(type[0], amount, trTime);
            transactions.emplace(trTime, newTransaction);
        }
    }

    return transactions;
}

void FileHandler::saveData(const list<User>& list) {
    // TODO: implement method
}
