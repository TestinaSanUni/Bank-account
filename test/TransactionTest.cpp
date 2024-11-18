//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../Transaction.h"

// the date is: 31/05/2024 - 1717133340
class TransactionSuite : public ::testing::Test {
protected:
    void SetUp() override {
        t = Transaction(1717133340, 2, 10);
    }

    Transaction t;
};

TEST(Transaction, DefaultConstructorTest) {
    Transaction t;
    ASSERT_EQ(t.getTrTime(), 0);
    ASSERT_EQ(t.getOperation(), 1);
    ASSERT_EQ(t.getAmount(), 0);
    ASSERT_EQ(t.getAccount(), "");
    ASSERT_EQ(t.getRole(), false);
}

TEST_F(TransactionSuite, CustomConstructorTest) {
    ASSERT_EQ(t.getTrTime(), 1717133340);
    ASSERT_EQ(t.getOperation(), 2);
    ASSERT_EQ(t.getAmount(), 10);
    ASSERT_EQ(t.getAccount(), "");
    ASSERT_EQ(t.getRole(), false);
}

TEST_F(TransactionSuite, EditTransactionTest) {
    t.setOperation(3);
    t.setAmount(20);
    t.setRecipient("recipient");
    t.setRole(false);

    ASSERT_EQ(t.getTrTime(), 1717133340);
    ASSERT_EQ(t.getOperation(), 3);
    ASSERT_EQ(t.getAmount(), 20);
    ASSERT_EQ(t.getAccount(), "recipient");
    ASSERT_EQ(t.getRole(), false);
}
