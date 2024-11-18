//
// Created by Testa on 5/25/2024.
//

#include "BankAccount.h"

list<time_t> BankAccount::getTransactions() const {
    list<time_t> l;

    for(const auto& i : transactions)
        l.push_back(i.first);

    return l;
}

// ======================================================================================
//      MAIN METHODS
// ======================================================================================

int BankAccount::addTransaction(time_t t, int o, float a) {
    Transaction newTransaction;

    if(t == 0) newTransaction = Transaction(std::time(&t), o, a);
    else newTransaction = Transaction(t, o, a);

    if(o == 2) {
        if (a < 0) a *= -1;
        if (balance >= a) balance -= a;
        else return 5; // insufficient balance
    } else balance += a;

    transactions.emplace(t, newTransaction);
    return 0;
}

int BankAccount::addTransaction(time_t t, int o, float a, const std::string &u, bool r) {
    if(name == u) return 7; // sender and recipient are the same

    Transaction newTransaction;

    if(t == 0) newTransaction = Transaction(std::time(&t), o, a, u, r);
    else newTransaction = Transaction(t, o, a, u, r);

    if(r) {
        if (a < 0) a *= -1;
        if (balance >= a) balance -= a;
        else return 5; // insufficient balance
    } else balance += a;

    transactions.emplace(t, newTransaction);
    return 0;
}

void BankAccount::printAccount() const {
    int counter = 1;
    cout << "\t" << name << " - $" << balance << endl;

    for(const auto& i : transactions) {
        i.second.printTransaction();
        cout << "[#" << counter << "]" << endl;
        counter++;
    }

    cout << endl;
}

map<time_t, Transaction> BankAccount::getByOp(int op) const {
    map<time_t, Transaction> t;

    if(op >= 1 && op <= 3) {
        for (const auto &i: transactions)
            if (i.second.getOperation() == op)
                t.emplace(i);
    }

    return t;
}

map<time_t, Transaction> BankAccount::getByDate(const std::string &date) const {
    map<time_t, Transaction> t;

    if (checkData(date)) {
        for (const auto &i: transactions)
            if (formatData(i.second.getTrTime()) == date)
                t.emplace(i);
    }

    return t;
}

int BankAccount::editTransaction(int id, int o, float a) {
    Transaction t = getTransactionById(id);
    if(t.getTrTime() == 0) return 10; // transaction not found

    transactions[t.getTrTime()].setOperation(o);
    transactions[t.getTrTime()].setAmount(a);

    return 0;
}

int BankAccount::editTransaction(int id, int o, float a, const std::string &u, bool r) {
    Transaction t = getTransactionById(id);
    if(t.getTrTime() == 0) return 10; // transaction not found
    if(name == u) return 7; // sender and recipient are the same

    transactions[t.getTrTime()].setOperation(o);
    transactions[t.getTrTime()].setAmount(a);
    transactions[t.getTrTime()].setRecipient(u);
    transactions[t.getTrTime()].setRole(r);

    return 0;
}

int BankAccount::deleteTransaction(int id) {
    Transaction t = getTransactionById(id);
    if(t.getTrTime() == 0) return 10; // transaction not found
    return !transactions.erase(t.getTrTime());
}

void BankAccount::clearTransactions() {
    transactions.clear();
}

// ======================================================================================
//      AUXILIARY METHODS
// ======================================================================================

Transaction BankAccount::getTransactionById(int id) const {
    if(id > transactions.size()) return {};

    auto i = transactions.begin();
    for(int j = 1; j < id; j++) i++;

    return i->second;
}

string BankAccount::formatData(time_t time) {
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

bool BankAccount::checkData(const std::string& date) {
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
