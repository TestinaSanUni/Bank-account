//
// Created by Testa on 9/29/2024.
//

#include "gtest/gtest.h"
#include "../ProgramManager.h"

// the date is: 31/05/2024 - 1717133340
class ProgramManagerSuite : public ::testing::Test {
protected:
    void SetUp() override {
        map<time_t, Transaction> t;
        t.emplace(1717133340, Transaction(1717133340, 1, 10));

        map<string, BankAccount> b;
        b.emplace("account1", BankAccount("account1", 10, t)); // 10

        map<string, User> u;
        u.emplace("Mario Rossi", User("Mario Rossi", b));

        pM = ProgramManager(u);
    }

    ProgramManager pM;
};

TEST_F(ProgramManagerSuite, DefaultConstructorSaveDataTest) {
    pM.saveData();

    ProgramManager pM2;
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("account1").getBalance(), 10);
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getAmount(), 10);

    // resetting file
    pM2.deleteUser("Mario Rossi");
    pM2.saveData();
}

TEST_F(ProgramManagerSuite, AddUserTest) {
    ASSERT_EQ(pM.addUser("Luigi Verdi"), 0);
    ASSERT_EQ(pM.getUser("Luigi Verdi").getAccounts().empty(), true);
    ASSERT_EQ(pM.addUser("Luigi Verdi"), 3); // user already existing
}

TEST_F(ProgramManagerSuite, AddBankAccountTest) {
    ASSERT_EQ(pM.addBankAccount("Mario Rossi", "account2"), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getBalance(), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransactions().empty(), true);

    // errors
    ASSERT_EQ(pM.addBankAccount("Mario Rossiiiiii", "account3"), 1); // user not found
    ASSERT_EQ(pM.addBankAccount("Mario Rossi", "account2"), 4); // account already existing
}

TEST_F(ProgramManagerSuite, AddTransactionTest) {
    pM.addBankAccount("Mario Rossi", "account2");

    // deposit
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 10, 10, 1717133341), 0); // 10 + 10 = 20
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getBalance(), 20);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133341).getOperation(), 1);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133341).getAmount(), 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133341).getAccount(), "");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133341).getRole(), false);

    // withdrawal
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 2, 10, 1717133342), 0); // 20 - 10 = 10
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getBalance(), 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133342).getOperation(), 2);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133342).getAmount(), 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133342).getAccount(), "");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133342).getRole(), false);

    // bank transfert
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 3, 10, "account2", 1717133343), 0); // 10 - 10 = 0
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getBalance(), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133343).getOperation(), 3);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133343).getAmount(), 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133343).getAccount(), "account2");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133343).getRole(), true);

    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getBalance(), 10); // 0 + 10 = 10
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransaction(1717133343).getOperation(), 3);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransaction(1717133343).getAmount(), 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransaction(1717133343).getAccount(), "account1");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransaction(1717133343).getRole(), false);

    // errors
    ASSERT_EQ(pM.addTransaction("Mario Rossiii", "account1", 1, 31, 1717133344), 1); // user not found
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "accounttt", 1, 31, 1717133344), 2); // bank account not found
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 2, 100, 1717133344), 5); // insufficient balance
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 3, 100, "account2", 1717133344), 5); // insufficient balance
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 3, 41, "recipienttt", 1717133344), 6); // recipient account not found
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "account1", 3, 100, "account1", 1717133344), 7); // sender and recipient are the same
}

TEST_F(ProgramManagerSuite, GetByOpTest) {
    map<string, User> u = pM.getByOp(1);
    ASSERT_EQ(u.size(), 1);

    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getRole(), false);
}

TEST_F(ProgramManagerSuite, GetByDateTest) {
    map<string, User> u = pM.getByDate("31/05/2024");
    ASSERT_EQ(u.size(), 1);

    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getAmount(), 10);
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransaction(1717133340).getRole(), false);
}

TEST_F(ProgramManagerSuite, SearchAccountTest) {
    map<string, User> u = pM.searchAccount("acc");

    ASSERT_EQ(u.size(), 1);

    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getBalance(), 10);
    ASSERT_EQ(u["Mario Rossi"].getAccount("account1").getTransactions().empty(), true);
}

TEST_F(ProgramManagerSuite, EditUserTest) {
    pM.addUser("Luigi Verdi");

    ASSERT_EQ(pM.editUser("Mario Rossi", "Enzo Ferrari"), 0);

    // errors
    ASSERT_EQ(pM.editUser("Mario Rossi", "Enzo Ferrari"), 1); // user not found
    ASSERT_EQ(pM.editUser("Luigi Verdi", "Enzo Ferrari"), 3); // user already existing
}

TEST_F(ProgramManagerSuite, EditBankAccountTest) {
    pM.addBankAccount("Mario Rossi", "account2");
    ASSERT_EQ(pM.editAccount("Mario Rossi", "account2", "account3"), 0);

    // errors
    ASSERT_EQ(pM.editAccount("Mario Rossiii", "account2", "account3"), 1); // user not found
    ASSERT_EQ(pM.editAccount("Mario Rossi", "account2", "account3"), 2); // account not found
    ASSERT_EQ(pM.editAccount("Mario Rossi", "account3", "account1"), 4); // account already existing
}

TEST_F(ProgramManagerSuite, EditTransactionTest) {
    ASSERT_EQ(pM.editTransaction("Mario Rossi", "account1", 1, 2, 10), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getOperation(), 2);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getAmount(), 10);

    pM.addBankAccount("Mario Rossi", "account2");
    ASSERT_EQ(pM.editTransaction("Mario Rossi", "account1", 1, 3, 20, "account2", true), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getOperation(), 3);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getAmount(), 20);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getAccount(), "account2");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransaction(1717133340).getRole(), true);

    // errors
    ASSERT_EQ(pM.editTransaction("Mario Rossiii", "account1", 1, 2, 10), 1); // user not found
    ASSERT_EQ(pM.editTransaction("Mario Rossi", "account3", 10, 1, 10), 2); // account not found
    ASSERT_EQ(pM.editTransaction("Mario Rossi", "account1", 1, 3, 20, "account3", true), 6); // recipient account not found
    ASSERT_EQ(pM.editTransaction("Mario Rossi", "account1", 1, 3, 10, "account1", true), 7); // sender and recipient are the same
    ASSERT_EQ(pM.editTransaction("Mario Rossi", "account1", 10, 1, 10), 10); // transaction not found
}

TEST_F(ProgramManagerSuite, DeleteUserTest) {
    ASSERT_EQ(pM.deleteUser("Mario Rossi"), 0);

    // errors
    ASSERT_EQ(pM.deleteUser("Mario Rossi"), 1); // user not found
}

TEST_F(ProgramManagerSuite, DeleteBankAccountTest) {
    ASSERT_EQ(pM.deleteAccount("Mario Rossi", "account1"), 0);

    // errors
    ASSERT_EQ(pM.deleteAccount("Mario Rossiii", "account1"), 1); // user not found
    ASSERT_EQ(pM.deleteAccount("Mario Rossi", "account1"), 2); // account not found
}

TEST_F(ProgramManagerSuite, DeleteTransactionTest) {
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransactions().size(), 1);
    ASSERT_EQ(pM.deleteTransaction("Mario Rossi", "account1", 1), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransactions().size(), 0);

    // errors
    ASSERT_EQ(pM.deleteTransaction("Mario Rossiii", "account1", 1), 1); // user not found
    ASSERT_EQ(pM.deleteTransaction("Mario Rossi", "account2", 1), 2); // account not found
    ASSERT_EQ(pM.deleteTransaction("Mario Rossi", "account1", 10), 10); // transaction not found
}

TEST_F(ProgramManagerSuite, ClearTransactionsTest) {
    pM.addBankAccount("Mario Rossi", "account2");
    pM.addTransaction("Mario Rossi", "account2", 1, 10);

    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransactions().empty(), false);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransactions().empty(), false);

    pM.clearTransactions("Mario Rossi", "account1");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransactions().empty(), true);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransactions().empty(), false);

    pM.addTransaction("Mario Rossi", "account1", 1, 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransactions().empty(), false);

    pM.clearTransactions();
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account1").getTransactions().empty(), true);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("account2").getTransactions().empty(), true);
}
