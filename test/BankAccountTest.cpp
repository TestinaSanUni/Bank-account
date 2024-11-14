//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../BankAccount.h"

TEST(BankAccount, DefaultConstructorTest) {
    BankAccount bankAccount;
    ASSERT_EQ(bankAccount.getName(), "");
    ASSERT_EQ(bankAccount.getBalance(), 0);
}

TEST(BankAccount, CustomConstructorTest) {
    map<time_t, Transaction> transactions;
    transactions.emplace(1717133339, Transaction('D', 30, 1717133339));
    transactions.emplace(1717133338, Transaction('B', "recipient", true, 50, 1717133338));

    BankAccount bankAccount("name", 100, transactions);

    ASSERT_EQ(bankAccount.getName(), "name");
    ASSERT_EQ(bankAccount.getBalance(), 100);

    ASSERT_EQ(bankAccount.getTransaction(1717133339).getTrTime(), 1717133339);
    ASSERT_EQ(bankAccount.getTransaction(1717133339).getOperation(), 'D');
    ASSERT_EQ(bankAccount.getTransaction(1717133339).getAmount(), 30);

    ASSERT_EQ(bankAccount.getTransaction(1717133338).getTrTime(), 1717133338);
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getOperation(), 'B');
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getAccount(), "recipient");
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getRole(), true);
    ASSERT_EQ(bankAccount.getTransaction(1717133338).getAmount(), 50);


}

TEST(BankAccount, AddTransactionTest) {
    map<time_t, Transaction> transactions;
    BankAccount bankAccount("name", 20, transactions);

    // deposit
    bankAccount.addTransaction('D', 80, 1717133339);
    ASSERT_EQ(bankAccount.getBalance(), 100);
    ASSERT_EQ(bankAccount.getTransaction(1717133339).getOperation(), 'D');
    ASSERT_EQ(bankAccount.getTransaction(1717133339).getAmount(), 80);

    // withdrawal
    bankAccount.addTransaction('W', 50, 1717133340);
    ASSERT_EQ(bankAccount.getBalance(), 50);
    ASSERT_EQ(bankAccount.getTransaction(1717133340).getOperation(), 'W');
    ASSERT_EQ(bankAccount.getTransaction(1717133340).getAmount(), 50);

    // bank transfert
    bankAccount.addTransaction('B', "recipient", true, 20, 1717133341);

    ASSERT_EQ(bankAccount.getTransaction(1717133341).getAccount(), "recipient");
    ASSERT_EQ(bankAccount.getTransaction(1717133341).getRole(), true);
    ASSERT_EQ(bankAccount.getTransaction(1717133341).getOperation(), 'B');
    ASSERT_EQ(bankAccount.getTransaction(1717133341).getAmount(), 20);

    // insufficient balance
    ASSERT_EQ(bankAccount.addTransaction('W', 31, 1717133342), 5);
    ASSERT_EQ(bankAccount.addTransaction('B', "recipient", true, 31, 1717133342), 5);
}

TEST(BankAccount, ClearTransactionsTest) {
    map<time_t, Transaction> transactions;
    BankAccount bankAccount("name", 20, transactions);

    bankAccount.addTransaction('D', 50, 1717133340);
    ASSERT_EQ(bankAccount.getTransactions().empty(), 0);

    bankAccount.clearTransactions();
    ASSERT_EQ(bankAccount.getTransactions().empty(), 1);
}