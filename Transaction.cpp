//
// Created by Testa on 5/25/2024.
//

#include "Transaction.h"

void Transaction::printTransaction() const {
    cout << "\t\t" << operation << " " << sender << " " << recipient << " " << amount << " ";
    formatDate(trTime);
}

void Transaction::formatDate(time_t time) const {
    struct tm tm = *localtime(&time);
    printf("%02d/%02d/%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}