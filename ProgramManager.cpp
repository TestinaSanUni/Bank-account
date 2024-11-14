//
// Created by irene on 08/08/2024.
//

#include <algorithm>
#include "ProgramManager.h"

// ======================================================================================
//      MAIN METHODS
// ======================================================================================


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

int ProgramManager::addTransaction(const std::string &user, const std::string &account, int o, const std::string &u, float a, time_t t) {
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
    } else cout << "There are no transactions" << endl;
}

map<string, User> ProgramManager::getByOp(int operation) const {
    map<string, User> u;

    if(operation >= 1 && operation <= 3) {
        bool foundUser = false, foundAccount = false;
        Transaction temp;

        for (auto i: users) {
            map<string, BankAccount> bA;

            for (const auto &j: i.second.getAccounts()) {
                map<time_t, Transaction> t;

                for (const auto &k: i.second.getAccount(j).getTransactions()) {
                    temp = i.second.getAccount(j).getTransaction(k);

                    if (temp.getOperation() == operation) {
                        t.emplace(temp.getTrTime(), temp);
                        foundUser = true;
                        foundAccount = true;
                    }
                }

                if (foundAccount) {
                    foundAccount = false;
                    BankAccount bATemp(i.second.getAccount(j).getName(), i.second.getAccount(j).getBalance(), t);
                    bA.emplace(i.second.getAccount(j).getName(), bATemp);
                }
            }

            if (foundUser) {
                foundUser = false;
                User uTemp(i.first, bA);
                u.emplace(i.first, uTemp);
            }
        }
    } else cout << "Invalid Operation" << endl;

    return u;
}

map<string, User> ProgramManager::getByDate(const std::string& date) const {
    map<string, User> u;

    if(checkData(date)) {
        bool foundUser = false, foundAccount = false;
        Transaction temp;

        for (auto i: users) {
            map<string, BankAccount> bA;

            for (const auto &j: i.second.getAccounts()) {
                map<time_t, Transaction> t;

                for (const auto &k: i.second.getAccount(j).getTransactions()) {
                    temp = i.second.getAccount(j).getTransaction(k);

                    if (formatData(temp.getTrTime()) == date) {
                        t.emplace(temp.getTrTime(), temp);
                        foundUser = true;
                        foundAccount = true;
                    }
                }

                if (foundAccount) {
                    foundAccount = false;
                    BankAccount bATemp(i.second.getAccount(j).getName(), i.second.getAccount(j).getBalance(), t);
                    bA.emplace(i.second.getAccount(j).getName(), bATemp);
                }
            }

            if (foundUser) {
                foundUser = false;
                User uTemp(i.first, bA);
                u.emplace(i.first, uTemp);
            }
        }
    } else cout << "Invalid date" << endl;

    return u;
}

int ProgramManager::searchAccount(const std::string &user, const std::string &account) {
    if(!findUser(user)) return 1; // user not found
    return users[user].searchAccount(account);
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

int ProgramManager::editTransaction(const std::string &user, const std::string &account, int id, int o, const std::string &u, float a, bool r) {
    if(!findUser(user)) return 1; // user not found
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

string ProgramManager::formatData(time_t time) {
    struct tm tm = *localtime(&time);
    string date;

    if(tm.tm_mday < 10) date = "0" + to_string(tm.tm_mday);
    else date = to_string(tm.tm_mday);

    date = date + "/";

    if(tm.tm_mon + 1 < 10) date = date + "0" + to_string(tm.tm_mon + 1);
    else date = date + to_string(tm.tm_mon + 1);

    date = date + "/";

    date = date + to_string(tm.tm_year + 1900);

    return date;
}

bool ProgramManager::checkData(const std::string& date) {
    string dayS = date.substr(0, 2), monthS = date.substr(3, 2), yearS = date.substr(6, 4); // getting substrings
    int day = stoi(dayS), month = stoi(monthS), year = stoi(yearS); // convert strings into ints

    time_t t = time(&t);
    struct tm currYear = *localtime(&t);

    if(year >= 1900 && year <= currYear.tm_year + 1900) {
        if(month > 0 && month < 13) {
            // month with 30 days
            if(month == 4  || month == 6 || month == 9 || month == 11) {
                if(day > 0 &&  day <= 30)
                    return true;
            } else if(month == 2) {
                // february
                if (year % 4 == 0) {
                    if (day > 0 && day <= 29)
                        return true;
                } else {
                    if (day > 0 && day <= 28)
                        return true;
                }
            } else {
                // other months
                if(day > 0 && day <= 31)
                    return true;
            }
        }
    }

    return false;
}
