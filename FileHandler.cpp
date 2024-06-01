//
// Created by Testa on 5/26/2024.
//

#include "FileHandler.h"
#include <iostream>

list<User> FileHandler::loadData() {
    list<User> users;
    file.open("Data.txt", ios::in);

    if(file.is_open()) {
        list<BankAccount> accounts;
        string name, surname;

        while(!file.eof() && file >> name && file >> surname) {
            accounts = loadBankAccounts();
            User newUser(name, surname, accounts);
            users.push_back(newUser);
        }

        file.close();
    }

    return users;
}

list<BankAccount> FileHandler::loadBankAccounts() {
    list<BankAccount> accounts;
    list<Transaction> transactions;
    string iban;
    float balance;

    while(file >> iban && iban != "end_accounts" && file >> balance) {
        transactions = loadTransactions(iban);
        BankAccount newBankAccount(iban, balance, transactions);
        accounts.push_back(newBankAccount);
    }

    return accounts;
}

list<Transaction> FileHandler::loadTransactions(const string& author) {
    list<Transaction> transactions;
    string type;
    string iban;
    bool role;
    float amount;
    time_t trTime;


    while(file >> type && type != "end_transactions") {
        if (type == "B") {
            file >> iban, file >> role, file >> amount, file >> trTime;
            Transaction newTransaction(type[0], iban, role, amount, trTime);
            transactions.push_back(newTransaction);
        } else {
            file >> amount, file >> trTime;
            Transaction newTransaction(type[0], amount, trTime);
            transactions.push_back(newTransaction);
        }
    }

    return transactions;
}

void FileHandler::saveData(const list<User>& list) {
    // TODO: implement method
}