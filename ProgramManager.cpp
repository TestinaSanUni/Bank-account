//
// Created by irene on 08/08/2024.
//

#include <algorithm>
#include "ProgramManager.h"

// ======================================================================================
//      MAIN METHODS
// ======================================================================================

User ProgramManager::getUser(const std::string &user) {
    if(!findUser(user)) return User();
    return users[user];
}

// ========================================= Adds ===============================================

int ProgramManager::addUser(const std::string &user) {
    if(findUser(user)) return 3; // user already existing
    users.emplace(user, User(user));
    return 0;
}

int ProgramManager::addBankAccount(const std::string &user, const std::string &account) {
    if(!findUser(user)) return 1; // user not found
    return users[user].addAccount(account);
}

int ProgramManager::addTransaction(const std::string &user, const std::string &account, int o, float a, time_t t) {
    if(!findUser(user)) return 1; // user not found
    return users[user].addTransaction(account, t, o, a);
}

int ProgramManager::addTransaction(const std::string &user, const std::string &account, int o, float a, const std::string &u, time_t t) {
    if(!findUser(user)) return 1; // user not found

    string recipient = findRecipientByAccount(u);
    if(recipient == " ") return 6; // recipient account not found

    int result = users[user].addTransaction(account, t, o, a, u, true);
    if(!result) result = users[recipient].addTransaction(u, t, o, a, account, false);
    return result;
}


// ======================================== Prints ==============================================

void ProgramManager::printInfo() const {
    cout << " ---------------------------------------------------------------------- " << endl;

    for (const auto &i: users) {
        i.second.printUser();
        cout << " ---------------------------------------------------------------------- " << endl;
    }
}

void ProgramManager::printInfo(const map<string, User>& u) {
    if(!u.empty()) {
        cout << " ---------------------------------------------------------------------- " << endl;

        for (const auto &i: u) {
            i.second.printUser();
            cout << " ---------------------------------------------------------------------- " << endl;
        }
    } else cout << "No information has been found" << endl;
}

map<string, User> ProgramManager::getByOp(int operation) const {
    map<string, User> m;

    for (const auto& i : users) {
        map<string, BankAccount> bA = i.second.getByOp(operation);

        if (!bA.empty()) {
            User u = User(i.first, bA);
            m.emplace(i.first, u);
        }
    }

    return m;
}

map<string, User> ProgramManager::getByDate(const std::string &date) const {
    map<string, User> m;

    for (const auto& i : users) {
        map<string, BankAccount> bA = i.second.getByDate(date);

        if (!bA.empty()) {
            User u = User(i.first, bA);
            m.emplace(i.first, u);
        }
    }

    return m;
}

map<string, User> ProgramManager::searchAccount(const std::string &account) const {
    map<string, User> m;

    for (const auto& i : users) {
        map<string, BankAccount> bA = i.second.searchAccount(account);

        if (!bA.empty()) {
            User u = User(i.first, bA);
            m.emplace(i.first, u);
        }
    }

    return m;
}


// ======================================== Edits ===============================================

int ProgramManager::editUser(const string &oldName, const string &newName) {
    if(!findUser(oldName)) return 1; // user not found
    if(findUser(newName)) return 3; // user already existing

    users.emplace(newName, users[oldName]);
    deleteUser(oldName);
    users[newName].setName(newName);
    return 0;
}

int ProgramManager::editAccount(const string &user, const string &oldAccount, const string &newAccount) {
    if(!findUser(user)) return 1; // user not found
    return users[user].editAccount(oldAccount, newAccount);
}

int ProgramManager::editTransaction(const std::string &user, const std::string &account, int id, int o, float a) {
    if(!findUser(user)) return 1; // user not found
    return users[user].editTransaction(account, id, o, a);
}

int ProgramManager::editTransaction(const std::string &user, const std::string &account, int id, int o, float a, const std::string &u, bool r) {
    if(!findUser(user)) return 1; // user not found
    if(findRecipientByAccount(u) == " ") return 6; // recipient account not found

    return users[user].editTransaction(account, id, o, a, u, r);
}

// ======================================== Deletes ==============================================

int ProgramManager::deleteUser(const std::string &user) {
    return !users.erase(user);
}

int ProgramManager::deleteAccount(const string &user, const string &account) {
    if(!findUser(user)) return 1; // user not found
    return users[user].deleteAccount(account);
}

int ProgramManager::deleteTransaction(const std::string &user, const std::string &account, int id) {
    if(!findUser(user)) return 1; // user not found
    return users[user].deleteTransaction(account, id);
}

void ProgramManager::clearTransactions(const std::string &user, const std::string &account) {
    if(findUser(user))
        users[user].clearTransactions(account);
}

void ProgramManager::clearTransactions() {
    for(auto& i : users)
        i.second.clearTransactions();
}

bool ProgramManager::saveData() {
    return fileHandler.saveData(users);
}


// ======================================================================================
//      AUXILIARY METHODS
// ======================================================================================

bool ProgramManager::findUser(const string& user) const {
    return users.find(user) != users.end();
}

string ProgramManager::findRecipientByAccount(const string& account) {
    for(auto i : users) {
        for(const auto& j : i.second.getAccounts()) {
            if(i.second.getAccount(j).getName() == account)
                return i.first;
        }
    }
    return " ";
}
