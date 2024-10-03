//
// Created by irene on 08/08/2024.
//

#include <algorithm>
#include "ProgramManager.h"

// ======================================================================================
//      BASIC METHODS
// ======================================================================================

int ProgramManager::setUserName(const std::string &oldName, const std::string &newName) {
    if(!findUser(oldName)) return 1; // user not found
    if(findUser(newName)) return 3; // user already existing

    users.emplace(newName, users[oldName]);
    deleteUser(oldName);
    users[newName].setName(newName);
    return 0;
}


// ======================================================================================
//      MAIN METHODS
// ======================================================================================

int ProgramManager::addUser(const std::string &name) {
    if(findUser(name)) return 3; // user already existing

    users.emplace(name, User(name));
    return 0;
}

int ProgramManager::addBankAccount(const std::string &name, const std::string &iban) {
    if(!findUser(name)) return 1; // user not found
    if(!checkAllIban(iban)) return 4; // account already existing

    users[name].addBankAccount(iban);
    return 0;
}

int ProgramManager::addTransaction(const std::string &name, const std::string &iban, char o, float a, time_t t) {
    if(!findUser(name)) return 1; // user not found

    return users[name].addTransaction(iban, o, a, t);
}

int ProgramManager::addTransaction(const std::string &name, const std::string &iban, char o, const std::string &u, float a, time_t t) {
    string recipientName = findRecipientBankAccount(u);

    if(!findUser(name)) return 1; // user not found
    if(recipientName == " ") return 6; // recipient account not found
    if(iban == u) return 7; // sender and recipient are the same

    int result = users[name].addTransaction(iban, o, u, true, a, t);
    if(!result) users[recipientName].addTransaction(u, o, iban, false, a, t);
    return result;
}

// ======================================== Prints ==============================================

void ProgramManager::printInfo() const {
    cout << " ---------------------------------------------------------------------- " << endl;
    for(const auto& i : users) {
        i.second.printUser();
        cout << " ---------------------------------------------------------------------- " << endl;
    }
}

int ProgramManager::printInfo(char operation) {
    bool foundUser = false, foundAccount = false, foundTransaction = false;

    for(const auto& i : users) {
        for(const auto& j : i.second.getBankAccounts()) {
            for (const auto &k: j.second.getTransactions()) {
                if (k.second.getOperation() == operation) {
                    if(!foundTransaction) cout << endl << " ---------------------------------------------------------------------- " << endl;
                    if(!foundUser) cout << endl << i.first << endl;
                    if(!foundAccount) cout << "\t" << j.first << endl;

                    foundUser = true;
                    foundAccount = true;
                    foundTransaction = true;

                    k.second.printTransaction();
                }
            }

            foundAccount = false;
            if(foundUser) cout << endl; // print alignment
        }

        if(foundUser) { // print alignment
            foundUser = false;
            cout << " ---------------------------------------------------------------------- " << endl;
        }
    }

    if(!foundTransaction) return 8;
    return 0;
}

int ProgramManager::printInfo(std::string date) {
    bool foundUser = false, foundAccount = false, foundTransaction = false;

    if(checkData(date)) {
        for(const auto& i : users) {
            for(const auto& j : i.second.getBankAccounts()) {
                for (const auto &k: j.second.getTransactions()) {
                    if(formatData(k.second.getTrTime()) == date) {
                        if(!foundTransaction) cout << endl << " ---------------------------------------------------------------------- " << endl;
                        if(!foundUser) cout << endl << i.first << endl;
                        if(!foundAccount) cout << "\t" << j.first << endl;

                        foundUser = true;
                        foundAccount = true;
                        foundTransaction = true;

                        k.second.printTransaction();
                    }
                }

                foundAccount = false;
                if(foundUser) cout << endl; // print alignment
            }

            if(foundUser) { // print alignment
                foundUser = false;
                cout << " ---------------------------------------------------------------------- " << endl;
            }
        }

        if(!foundTransaction) return 8;
    } else return 9;
    return 0;
}

// ======================================== Clears ==============================================

void ProgramManager::clearTransactions() {
    for(auto& i : users)
        i.second.clearTransactions();
}

void ProgramManager::clearTransactions(const std::string &name, const std::string &iban) {
    if(findUser(name))
        users[name].clearTransactions(iban);
}

// ======================================== Deletes ==============================================

int ProgramManager::deleteUser(const std::string &name) {
    return !users.erase(name);
}

int ProgramManager::deleteBankAccount(const std::string &name, const std::string &iban) {
    if(!findUser(name)) return 1; // user not found

    return users[name].deleteBankAccount(iban);
}

bool ProgramManager::saveData() {
    return fileHandler.saveData("Data.txt", users);
}


// ======================================================================================
//      AUXILIARY METHODS
// ======================================================================================

bool ProgramManager::findUser(const string& name) const {
    return users.find(name) != users.end();
}

string ProgramManager::findRecipientBankAccount(const string& iban) {
    for(const auto& i : users) {
        for(const auto& j : i.second.getBankAccounts()) {
            if(j.second.getIban() == iban)
                return i.first;
        }
    }
    return " ";
}

bool ProgramManager::checkAllIban(const std::string &iban) {
    for(const auto& i : users)
        if(i.second.findBankAccount(iban))
            return false;
    return true;
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
