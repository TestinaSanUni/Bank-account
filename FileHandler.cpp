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
        transactions = loadTransactions();
        BankAccount newBankAccount(iban, balance, transactions);
        accounts.emplace(iban, newBankAccount);
    }

    return accounts;
}

map<time_t, Transaction> FileHandler::loadTransactions() {
    map<time_t, Transaction> transactions;
    string type, iban;
    bool role;
    float amount;
    time_t trTime;

    while(file >> type && type != "end_transactions") {
        if (type == "3") {
            file >> iban, file >> role, file >> amount, file >> trTime;
            Transaction newTransaction(trTime, stoi(type), amount, iban, role);
            transactions.emplace(trTime, newTransaction);
        } else {
            file >> amount, file >> trTime;
            Transaction newTransaction(trTime, stoi(type), amount);
            transactions.emplace(trTime, newTransaction);
        }
    }

    return transactions;
}

bool FileHandler::saveData(const map<string, User>& users) {
    file.open("Data.txt", ios::out);

    if(!file.is_open())
        return false;

    for(auto i: users) {
        file << i.first << endl;

        for(const auto& j : i.second.getAccounts()) {
            file << i.second.getAccount(j).getName() << " " << i.second.getAccount(j).getBalance() << endl;

            for(const auto& k : i.second.getAccount(j).getTransactions()) {
                if(i.second.getAccount(j).getTransaction(k).getOperation() == 3) {
                    file << i.second.getAccount(j).getTransaction(k).getOperation() << " ";
                    file << i.second.getAccount(j).getTransaction(k).getAccount() << " ";
                    file << i.second.getAccount(j).getTransaction(k).getRole() << " ";
                    file << i.second.getAccount(j).getTransaction(k).getAmount() << " ";
                    file << i.second.getAccount(j).getTransaction(k).getTrTime() << endl;
                } else {
                    file << i.second.getAccount(j).getTransaction(k).getOperation() << " ";
                    file << i.second.getAccount(j).getTransaction(k).getAmount() << " ";
                    file << i.second.getAccount(j).getTransaction(k).getTrTime() << endl;
                }
            }
            file << "end_transactions" << endl;
        }
        file << "end_accounts" << endl << endl;
    }

    file.close();
    return true;
}
