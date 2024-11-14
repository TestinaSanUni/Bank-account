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
    Transaction() {
        trTime = 0;
        operation = 1;
        amount = 0;
        recipient = "";
        role = false;
    }

    Transaction(time_t t, int o, float a) : trTime(t), operation(o), amount(a) {
        if(o < 1 || o > 3) operation = 1;
        if(a < 0) amount = a * -1;
        recipient = "";
        role = false;
    }

    Transaction(time_t t, int o, float a, const string& u, bool r) : trTime(t), operation(o), amount(a), recipient(u), role(r) {
        if(o < 1 || o > 3) operation = 1;
        if(a < 0) amount = a * -1;
    }

    time_t getTrTime() const { return trTime; }
    int getOperation() const { return operation; }
    float getAmount() const { return amount; }
    string getAccount() const { return recipient; }
    bool getRole() const { return role; }

    void setOperation(int o) { operation = o; }
    void setAmount(float a) { amount = a; }
    void setRecipient(const string& r) { recipient = r; }
    void setRole(bool r) { role = r; }

    void printTransaction() const;

private:
    static string formatOperation(int op); // print the actual operation
    void formatDate() const; // print the actual date

    time_t trTime;
    int operation;
    float amount;
    string recipient;
    bool role; // indicates which account sends / receives money
};


#endif //BANK_ACCOUNT_TRANSACTION_H
