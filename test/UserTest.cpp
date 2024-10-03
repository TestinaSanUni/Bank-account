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

TEST(User, SetNameTest) {
    User user("Mario");

    user.setName("Luigi");
    ASSERT_EQ(user.getName(), "Luigi");
}

TEST(User, AddBankAccountTest) {
    User user;
    user.addBankAccount("iban");
    ASSERT_EQ(user.getBankAccount("iban").getIban(), "iban");
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 0);
}

TEST(User, AddTransactionTest) {
    User user;
    user.addBankAccount("iban");

    user.addTransaction("iban", 'D', 80, 1717133339);
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 80);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133339).getOperation(), 'D');
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133339).getAmount(), 80);

    // withdrawal
    user.addTransaction("iban", 'W', 30, 1717133340);
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 50);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133340).getOperation(), 'W');
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133340).getAmount(), 30);

    // bank transfert
    user.addTransaction("iban", 'B', "recipient", true, 20, 1717133341);
    ASSERT_EQ(user.getBankAccount("iban").getBalance(), 30);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133341).getAccount(), "recipient");
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133341).getRole(), true);
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133341).getOperation(), 'B');
    ASSERT_EQ(user.getBankAccount("iban").getTransaction(1717133341).getAmount(), 20);

    // insufficient balance
    ASSERT_EQ(user.addTransaction("iban", 'W', 31, 1717133342), 5);
    ASSERT_EQ(user.addTransaction("iban", 'B', "recipient", true, 31, 1717133342), 5);

    // bank account not found
    ASSERT_EQ(user.addTransaction("ibannnn", 'W', 31, 1717133342), 2);
}

TEST(User, DelBankAccountTest) {
    User user;
    user.addBankAccount("iban");
    ASSERT_EQ(user.deleteBankAccount("iban"), 0);
    ASSERT_EQ(user.deleteBankAccount("iban"), 2);
}

TEST(User, FindBankAccountTest) {
    User user;
    user.addBankAccount("iban");
    ASSERT_EQ(user.findBankAccount("iban"), 1);
    ASSERT_EQ(user.findBankAccount("ibannnn"), 0);
}

TEST(User, ClearTransactionsTest) {
    User user;
    user.addBankAccount("iban1");
    user.addTransaction("iban1", 'D', 10, 1717133339);
    user.addBankAccount("iban2");
    user.addTransaction("iban2", 'D', 10, 1717133339);

    ASSERT_EQ(user.getBankAccount("iban1").getTransactions().empty(), 0);
    ASSERT_EQ(user.getBankAccount("iban2").getTransactions().empty(), 0);
    user.clearTransactions("iban1");
    ASSERT_EQ(user.getBankAccount("iban1").getTransactions().empty(), 1);
    ASSERT_EQ(user.getBankAccount("iban2").getTransactions().empty(), 0);

    user.addTransaction("iban1", 'D', 10, 1717133339);
    ASSERT_EQ(user.getBankAccount("iban1").getTransactions().empty(), 0);
    ASSERT_EQ(user.getBankAccount("iban2").getTransactions().empty(), 0);
    user.clearTransactions();
    ASSERT_EQ(user.getBankAccount("iban1").getTransactions().empty(), 1);
    ASSERT_EQ(user.getBankAccount("iban2").getTransactions().empty(), 1);
}
