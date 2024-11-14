//
// Created by Testa on 5/25/2024.
//

#include "Transaction.h"

void Transaction::printTransaction() const {
    if(operation == 3) {
        if (role)
            cout << "\t\t" << formatOperation(operation) << " to " << recipient << " $" << amount << " - ";
        else
            cout << "\t\t" << formatOperation(operation) << " from " << recipient << " $" << amount << " - ";
    } else cout << "\t\t" << formatOperation(operation) << " $" << amount << " - ";
    formatDate();
}

string Transaction::formatOperation(int op) {
    if(op == 1) return "Deposit";
    if(op == 2) return "Withdrawal";
    return "Bank transfert";
}

void Transaction::formatDate() const {
    struct tm tm = *localtime(&trTime);
    printf("%02d/%02d/%d %02d:%02d:%02d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}