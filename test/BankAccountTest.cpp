//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../BankAccount.h"

// the date is: 31/05/2024 - 1717133340
class BankAccountSuite : public ::testing::Test {
protected:
    void SetUp() override {
        map<time_t, Transaction> m;
        m.emplace(1717133340, Transaction(1717133340, 1, 30));
        bA = BankAccount("account", 10, m); // 10
    }

    BankAccount bA;
};

TEST(BankAccount, DefaultConstructorTest) {
    BankAccount bA;
    ASSERT_EQ(bA.getName(), "");
    ASSERT_EQ(bA.getBalance(), 0);
    ASSERT_EQ(bA.getTransactions().size(), 0);
}

TEST_F(BankAccountSuite, CustomConstructorTest) {
    ASSERT_EQ(bA.getName(), "account");
    ASSERT_EQ(bA.getBalance(), 10);
    ASSERT_EQ(bA.getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(bA.getTransaction(1717133340).getAmount(), 30);
    ASSERT_EQ(bA.getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(bA.getTransaction(1717133340).getRole(), false);
}

TEST_F(BankAccountSuite, AddTransactionTest) {
    // deposit
    ASSERT_EQ(bA.addTransaction(1717133341, 20, 10), 0); // 10 + 10 = 20
    ASSERT_EQ(bA.getBalance(), 20);
    ASSERT_EQ(bA.getTransaction(1717133341).getOperation(), 1);
    ASSERT_EQ(bA.getTransaction(1717133341).getAmount(), 10);

    // withdrawal
    ASSERT_EQ(bA.addTransaction(1717133342, 2, 10), 0); // 20 - 10 = 10
    ASSERT_EQ(bA.getBalance(), 10);
    ASSERT_EQ(bA.getTransaction(1717133342).getOperation(), 2);
    ASSERT_EQ(bA.getTransaction(1717133342).getAmount(), 10);

    // bank transfert
    ASSERT_EQ(bA.addTransaction(1717133343, 3, 10, "recipient", true), 0); // 10 - 10 = 0
    ASSERT_EQ(bA.getBalance(), 0);
    ASSERT_EQ(bA.getTransaction(1717133343).getOperation(), 3);
    ASSERT_EQ(bA.getTransaction(1717133343).getAmount(), 10);
    ASSERT_EQ(bA.getTransaction(1717133343).getAccount(), "recipient");
    ASSERT_EQ(bA.getTransaction(1717133343).getRole(), true);

    // errors
    ASSERT_EQ(bA.addTransaction(1717133344, 2, 100), 5); // insufficient balance
    ASSERT_EQ(bA.addTransaction(1717133344, 3, 100, "recipient", true), 5); // insufficient balance
    ASSERT_EQ(bA.addTransaction(1717133344, 3, 100, "account", true), 7); // sender and recipient are the same
}


TEST_F(BankAccountSuite, GetByOpTest) {
    map<time_t, Transaction> t = bA.getByOp(1);

    ASSERT_EQ(t.size(), 1);
    ASSERT_EQ(t[1717133340].getOperation(), 1);
    ASSERT_EQ(t[1717133340].getAmount(), 30);
    ASSERT_EQ(t[1717133340].getAccount(), "");
    ASSERT_EQ(t[1717133340].getRole(), false);

    // errors
    t = bA.getByOp(5);
    ASSERT_EQ(t.empty(), true);
}

TEST_F(BankAccountSuite, GetByDateTest) {
    map<time_t, Transaction> t = bA.getByDate("31/05/2024");

    ASSERT_EQ(t.size(), 1);

    ASSERT_EQ(t[1717133340].getOperation(), 1);
    ASSERT_EQ(t[1717133340].getAmount(), 30);
    ASSERT_EQ(t[1717133340].getAccount(), "");
    ASSERT_EQ(t[1717133340].getRole(), false);

    // errors
    t = bA.getByDate("32/05/2024"); // incorrect date
    ASSERT_EQ(t.empty(), true);
}

TEST_F(BankAccountSuite, EditTransactionTest) {
    ASSERT_EQ(bA.editTransaction(1, 3, 10, "recipient", true), 0);

    ASSERT_EQ(bA.getTransaction(1717133340).getOperation(), 3);
    ASSERT_EQ(bA.getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(bA.getTransaction(1717133340).getAccount(), "recipient");
    ASSERT_EQ(bA.getTransaction(1717133340).getRole(), true);

    // errors
    ASSERT_EQ(bA.editTransaction(10, 3, 10, "recipient", true), 10); // transaction not found
    ASSERT_EQ(bA.editTransaction(1, 3, 10, "account", true), 7); // sender and recipient are the same
}

TEST_F(BankAccountSuite, DeleteTransactionTest) {
    ASSERT_EQ(bA.getTransactions().size(), 1);
    ASSERT_EQ(bA.deleteTransaction(1), 0);
    ASSERT_EQ(bA.getTransactions().size(), 0);

    // errors
    ASSERT_EQ(bA.deleteTransaction(10), 10); // transaction not found
}

TEST_F(BankAccountSuite, ClearTransactionsTest) {
    bA.addTransaction(1717133341, 1, 20);

    ASSERT_EQ(bA.getTransactions().size(), 2);
    bA.clearTransactions();
    ASSERT_EQ(bA.getTransactions().empty(), true);
}