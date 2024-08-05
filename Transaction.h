//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_TRANSACTION_H
#define BANK_ACCOUNT_TRANSACTION_H
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Transaction {
public:
    Transaction() = default;
    Transaction(char o, float a, time_t t) : operation(o), amount(a), trTime(t) {}
    Transaction(char o, const string& u, bool r, float a, time_t t) : operation(o), account(u), role(r), amount(a), trTime(t) {}

    char getOperation() const { return operation; }
    string getAccount() const { return account; }
    bool getRole() const { return role; }
    float getAmount() const { return amount; }
    time_t getTrTime() const { return trTime; }

    void printTransaction() const;

private:
    void formatDate() const; // convert the integer value given by the method time into an actual date

    char operation = ' ';
    string account;
    bool role = false; // indicates the role of the other account during the bank transfer (sender/recipient)
    float amount = 0;
    time_t trTime = 0;
};


#endif //BANK_ACCOUNT_TRANSACTION_H
