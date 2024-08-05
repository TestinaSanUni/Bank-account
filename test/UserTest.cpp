//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../User.h"

TEST(User, DefaultConstructorTest) {
    User user;
    ASSERT_EQ(user.getName(), "");
    ASSERT_EQ(user.getBankAccount("iban").getIban(), "");
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 0);
}

TEST(User, CustomConstructorTest) {
    map<time_t, Transaction> transactions;
    transactions.emplace(1717133338, Transaction('B', "recipient", true, 50, 1717133338));
    map<string, BankAccount> accounts;
    accounts.emplace("iban", BankAccount("iban", 100, transactions));
    User user("user", accounts);
    ASSERT_EQ(user.getName(), "user");
    ASSERT_EQ(user.getBankAccount("iban").getIban(), "iban");
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 100);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133338).getTrTime(), 1717133338);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133338).getOperation(), 'B');
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133338).getAccount(), "recipient");
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133338).getRole(), true);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133338).getAmount(), 50);
}

TEST(User, AddBankAccountTest) {
    User user;
    user.addBankAccount("iban", 200);
    ASSERT_EQ(user.getBankAccount("iban").getIban(), "iban");
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 200);
}

TEST(User, DelBankAccountTest) {
    User user;
    user.addBankAccount("iban", 200);
    ASSERT_EQ(user.deleteBankAccount("iban"), true);
    ASSERT_EQ(user.deleteBankAccount("iban"), false);
}
