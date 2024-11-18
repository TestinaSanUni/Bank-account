//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../User.h"

// the date is: 31/05/2024 - 1717133340
class UserSuite : public ::testing::Test {
protected:
    void SetUp() override {
        map<time_t, Transaction> t;
        t.emplace(1717133340, Transaction(1717133340, 1, 10));

        map<string, BankAccount> bA;
        bA.emplace("account1", BankAccount("account1", 10, t)); // 10

        u = User("Mario Rossi", bA);
    }

    User u;
};

TEST(User, DefaultConstructorTest) {
    User user;
    ASSERT_EQ(user.getName(), "");
    ASSERT_EQ(user.getAccounts().empty(), true);
}

TEST_F(UserSuite, CustomConstructorTest) {
    ASSERT_EQ(u.getName(), "Mario Rossi");
    ASSERT_EQ(u.getAccount("account1").getName(), "account1");
    ASSERT_EQ(u.getAccount("account1").getBalance(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getRole(), false);
}

TEST_F(UserSuite, AddBankAccountTest) {
    ASSERT_EQ(u.addAccount("account2"), 0);
    ASSERT_EQ(u.getAccount("account2").getBalance(), 0); // 0
    ASSERT_EQ(u.getAccount("account2").getTransactions().empty(), true);

    // errors
    ASSERT_EQ(u.addAccount("account2"), 4); // account already existing
}

TEST_F(UserSuite, AddTransactionTest) {
    // deposit
    ASSERT_EQ(u.addTransaction("account1", 1717133341, 10, 10), 0); // 10 + 10 = 20
    ASSERT_EQ(u.getAccount("account1").getBalance(), 20);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133341).getOperation(), 1);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133341).getAmount(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133341).getAccount(), "");
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133341).getRole(), false);

    // withdrawal
    ASSERT_EQ(u.addTransaction("account1", 1717133342, 2, 10), 0); // 20 - 10 = 10
    ASSERT_EQ(u.getAccount("account1").getBalance(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133342).getOperation(), 2);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133342).getAmount(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133342).getAccount(), "");
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133342).getRole(), false);

    // bank transfert
    ASSERT_EQ(u.addTransaction("account1", 1717133343, 3, 10, "recipient", true), 0); // 10 - 10 = 0
    ASSERT_EQ(u.getAccount("account1").getBalance(), 0);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133343).getOperation(), 3);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133343).getAmount(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133343).getAccount(), "recipient");
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133343).getRole(), true);

    // errors
    ASSERT_EQ(u.addTransaction("accounttttt", 1717133344, 1, 31), 2); // bank account not found
    ASSERT_EQ(u.addTransaction("account1", 1717133344, 2, 100), 5); // insufficient balance
    ASSERT_EQ(u.addTransaction("account1", 1717133344, 3, 100, "recipient", true), 5); // insufficient balance
    ASSERT_EQ(u.addTransaction("account1", 1717133344, 3, 100, "account1", true), 7); // sender and recipient are the same
}

TEST_F(UserSuite, GetByOpTest) {
    map<string, BankAccount> bA = u.getByOp(1);
    ASSERT_EQ(bA.size(), 1);

    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getRole(), false);
}

TEST_F(UserSuite, GetByDateTest) {
    map<string, BankAccount> bA = u.getByDate("31/05/2024");
    ASSERT_EQ(bA.size(), 1);

    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(bA["account1"].getTransaction(1717133340).getRole(), false);
}

TEST_F(UserSuite, SearchAccountTest) {
    map<string, BankAccount> bA = u.searchAccount("acc");

    ASSERT_EQ(bA.size(), 1);

    ASSERT_EQ(bA["account1"].getBalance(), 10);
    ASSERT_EQ(bA["account1"].getTransactions().empty(), true);
}

TEST_F(UserSuite, EditAccountTest) {
    u.addAccount("account2");

    ASSERT_EQ(u.editAccount("account2", "account3"), 0);

    // errors
    ASSERT_EQ(u.editAccount("account2", "account3"), 2); // account not found
    ASSERT_EQ(u.editAccount("account1", "account3"), 4); // account already existing
}

TEST_F(UserSuite, EditTransactionTest) {
    ASSERT_EQ(u.editTransaction("account1", 1, 2, 10), 0);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getOperation(), 2);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getRole(), false);

    ASSERT_EQ(u.editTransaction("account1", 1, 3, 20, "recipient", true), 0);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getOperation(), 3);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getAmount(), 20);
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getAccount(), "recipient");
    ASSERT_EQ(u.getAccount("account1").getTransaction(1717133340).getRole(), true);

    // errors
    ASSERT_EQ(u.editTransaction("account2", 1, 1, 10), 2); // account not found
    ASSERT_EQ(u.editTransaction("account1", 1, 3, 10, "account1", true), 7); // sender and recipient are the same
    ASSERT_EQ(u.editTransaction("account1", 10, 1, 10), 10); // transaction not found
}

TEST_F(UserSuite, DeleteAccountTest) {
    ASSERT_EQ(u.deleteAccount("account1"), 0);

    // errors
    ASSERT_EQ(u.deleteAccount("account1"), 2); // account not found
}

TEST_F(UserSuite, DeleteTransactionTest) {
    ASSERT_EQ(u.getAccount("account1").getTransactions().size(), 1);
    ASSERT_EQ(u.deleteTransaction("account1", 1), 0);
    ASSERT_EQ(u.getAccount("account1").getTransactions().size(), 0);

    // errors
    ASSERT_EQ(u.deleteTransaction("account2", 1), 2); // account not found
    ASSERT_EQ(u.deleteTransaction("account1", 10), 10); // transaction not found
}

TEST_F(UserSuite, ClearTransactionsTest) {
    u.addTransaction("account1", 1717133341, 3, 10, "recipient", true);
    ASSERT_EQ(u.getAccount("account1").getTransactions().size(), 2);

    u.clearTransactions();
    ASSERT_EQ(u.getAccount("account1").getTransactions().empty(), true);
}
