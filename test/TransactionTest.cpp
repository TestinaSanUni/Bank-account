//
// Created by irene on 04/08/2024.
//

#include "gtest/gtest.h"
#include "../Transaction.h"

TEST(Transaction, DefaultConstructorTest) {
    Transaction transaction;
    ASSERT_EQ(transaction.getOperation(), ' ');
    ASSERT_EQ(transaction.getAccount(), "");
    ASSERT_EQ(transaction.getRole(), false);
    ASSERT_EQ(transaction.getAmount(), 0);
    ASSERT_EQ(transaction.getTrTime(), 0);
}

TEST(Transaction, CustomConstructorTest) {
    Transaction transaction('W', 300, 1717231292);
    ASSERT_EQ(transaction.getOperation(), 'W');
    ASSERT_EQ(transaction.getAccount(), "");
    ASSERT_EQ(transaction.getRole(), false);
    ASSERT_EQ(transaction.getAmount(), 300);
    ASSERT_EQ(transaction.getTrTime(), 1717231292);

    transaction = Transaction('B', "recipient", true, 10, 1717231292);
    ASSERT_EQ(transaction.getOperation(), 'B');
    ASSERT_EQ(transaction.getAccount(), "recipient");
    ASSERT_EQ(transaction.getRole(), true);
    ASSERT_EQ(transaction.getAmount(), 10);
    ASSERT_EQ(transaction.getTrTime(), 1717231292);
}