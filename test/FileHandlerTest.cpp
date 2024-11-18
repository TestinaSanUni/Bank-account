//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../FileHandler.h"

TEST(FileHandler, LoadAndSaveDataTest) {
    map<time_t, Transaction> transactions;
    transactions.emplace(0, Transaction(1717133340, 1, 20));

    map<string, BankAccount> bankAccounts;
    bankAccounts.emplace("account", BankAccount("account", 20, transactions));

    map<string, User> users;
    users.emplace("Mario Rossi", User("Mario Rossi", bankAccounts));

    FileHandler fileHandler;
    fileHandler.saveData(users);

    map<string, User> userCheck = fileHandler.loadData();
    ASSERT_EQ(userCheck["Mario Rossi"].getAccount("account").getBalance(), 20);
    ASSERT_EQ(userCheck["Mario Rossi"].getAccount("account").getTransaction(1717133340).getOperation(), 1);
    ASSERT_EQ(userCheck["Mario Rossi"].getAccount("account").getTransaction(1717133340).getAmount(), 20);
    ASSERT_EQ(userCheck["Mario Rossi"].getAccount("account").getTransaction(1717133340).getAccount(), "");
    ASSERT_EQ(userCheck["Mario Rossi"].getAccount("account").getTransaction(1717133340).getRole(), false);
}
