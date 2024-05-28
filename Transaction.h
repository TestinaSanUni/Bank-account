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
    Transaction(char o, float a, const string& s, const string& r = "") : operation(o), amount(a), sender(s), recipient(r) {
        trTime = time(nullptr);
    }

    void printTransaction() const;

private:
    void formatDate(time_t time) const; // convert the integer value given by the method time into an actual date

    char operation;
    string sender;
    string recipient;
    float amount;
    time_t trTime;
};


#endif //BANK_ACCOUNT_TRANSACTION_H
