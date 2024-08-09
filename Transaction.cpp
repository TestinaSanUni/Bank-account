//
// Created by Testa on 5/25/2024.
//

#include "Transaction.h"

void Transaction::printTransaction() const {
    if(operation == 'B') {
        if (role)
            cout << "\t\t" << operation << " to " << recipient << " $" << amount << " - ";
        else
            cout << "\t\t" << operation << " from " << recipient << " $" << amount << " - ";
    } else cout << "\t\t" << operation << " $" << amount << " - ";
    formatDate();
}

void Transaction::formatDate() const {
    struct tm tm = *localtime(&trTime);
    printf("%02d/%02d/%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}