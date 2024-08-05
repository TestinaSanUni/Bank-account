//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../BankAccount.h"

TEST(BankAccount, DefaultConstructorTest) {
    BankAccount bankAccount;
    ASSERT_EQ(bankAccount.getIban(), "");
    ASSERT_EQ(bankAccount.getBalance(), 0);
}

TEST(BankAccount, CustomConstructorTest) {
    map<time_t, Transaction> transactions;
    transactions.emplace(1717133338, Transaction('B', "recipient", true, 50, 1717133338));
    BankAccount bankAccount("iban", 100, transactions);
    ASSERT_EQ(bankAccount.getIban(), "iban");
    ASSERT_EQ(bankAccount.getBalance(), 100);
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getTrTime(), 1717133338);
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getOperation(), 'B');
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getAccount(), "recipient");
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getRole(), true);
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getAmount(), 50);
}

TEST(BankAccount, AddTransactionTest) {
    map<time_t, Transaction> transactions;
    BankAccount bankAccount("iban", 20, transactions);
    bankAccount.addTransaction('W', 50, 1717231292);
    ASSERT_EQ(bankAccount.getBalance(), 20);
    ASSERT_EQ(bankAccount.getTransaction(1717231292).getTrTime(), 0);

    bankAccount.addTransaction('W', 20, 1717236292);
    ASSERT_EQ(bankAccount.getBalance(), 0);
    ASSERT_EQ(bankAccount.getTransaction(1717236292).getTrTime(), 1717236292);
    ASSERT_EQ(bankAccount.getTransaction(1717236292).getOperation(), 'W');
    ASSERT_EQ(bankAccount.getTransaction(1717236292).getAmount(), 20);
}