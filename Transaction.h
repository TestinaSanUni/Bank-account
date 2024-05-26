//
// Created by Testa on 5/25/2024.
//

#ifndef BANK_ACCOUNT_TRANSACTION_H
#define BANK_ACCOUNT_TRANSACTION_H
#include <string>
#include <ctime>
using namespace std;

class Transaction {
public:
    Transaction() = default;
    Transaction(char o, float a, const string& s, const string& r = "") : operation(o), amount(a), sender(s), recipient(r) {
        trTime = time(nullptr);
    }

    void printTransaction(); // print the transaction

private:
    char operation;
    string sender;
    string recipient;
    float amount;
    time_t trTime;
};


#endif //BANK_ACCOUNT_TRANSACTION_H
