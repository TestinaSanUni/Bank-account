//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../FileHandler.h"

TEST(FileHandler, LoadAndSaveDataTest) {
    map<time_t, Transaction> transactions;
    transactions.emplace(0, Transaction('D', 50, 0));

    map<string, BankAccount> bankAccounts;
    bankAccounts.emplace("iban", BankAccount("iban", 20, transactions));

    map<string, User> users;
    users.emplace("Mario Rossi", User("Mario Rossi", bankAccounts));

    FileHandler fileHandler;
    fileHandler.saveData("Data.txt", users);

    map<string, User> userCheck = fileHandler.loadData("Data.txt");
    ASSERT_EQ(userCheck["Mario Rossi"].getBankAccount("iban").getBalance(), 20);
    ASSERT_EQ(userCheck["Mario Rossi"].getBankAccount("iban").getTransaction(0).getOperation(), 'D');
    ASSERT_EQ(userCheck["Mario Rossi"].getBankAccount("iban").getTransaction(0).getAccount(), "");
    ASSERT_EQ(userCheck["Mario Rossi"].getBankAccount("iban").getTransaction(0).getRole(), false);
    ASSERT_EQ(userCheck["Mario Rossi"].getBankAccount("iban").getTransaction(0).getAmount(), 50);
}
