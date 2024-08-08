//
// Created by irene on 08/08/2024.
//

#include "ProgramManager.h"

void ProgramManager::addUser(const std::string &name) {
    User newUser(name);
    users.emplace(name, newUser);
}

bool ProgramManager::addBankAccount(const std::string &name, const std::string &iban) {
    if(findUser(name)) {
        users[name].addBankAccount(iban);
        return true;
    }
    return false;
}

bool ProgramManager::addTransaction(const std::string &name, const std::string &iban, char o, float a, time_t t) {
    if(findUser(name))
        return users[name].addTransaction(iban, o, a, t);

    return false;
}

bool ProgramManager::addTransaction(const std::string &name, const std::string &iban, char o, const std::string &u, float a, time_t t) {
    string recipientName = findRecipientBankAccount(u);

    if(findUser(name) && recipientName != " ")
        if(users[name].addTransaction(iban, o, u, true, a, t) && users[recipientName].addTransaction(u, o, iban, false, a, t))
            return true;
    return false;
}

bool ProgramManager::deleteUser(const std::string &name) {
    return users.erase(name);
}

bool ProgramManager::deleteBankAccount(const std::string &name, const std::string &iban) {
    if(findUser(name))
        return users[name].deleteBankAccount(iban);
    return false;
}

bool ProgramManager::saveData() {
    return fileHandler.saveData(users);
}

void ProgramManager::printUsers() const {
    for(const auto& i : users)
        i.second.printUser();
}

bool ProgramManager::findUser(const string& n) {
    return users.find(n) != users.end();
}

string ProgramManager::findRecipientBankAccount(const string& iban) {
    for(const auto& i : users) {
        for(const auto& j : i.second.getBankAccounts()) {
            if(j.second.getIban() == iban)
                return i.first;
        }
    }
    return "";
}
