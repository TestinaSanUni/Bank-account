//
// Created by Testa on 9/29/2024.
//

#include "gtest/gtest.h"
#include "../ProgramManager.h"

TEST(ProgramManager, DefaultConstructorTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addBankAccount("Mario Rossi", "name");
    pM.addTransaction("Mario Rossi", "name", 'D', 10, 1717133341);

    pM.saveData();

    ProgramManager pM2;
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getOperation(), 'D');
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getAmount(), 10);
    pM2.deleteUser("Mario Rossi");
    pM2.saveData();
}

TEST(ProgramManager, SetUserNameTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addUser("Enzo Ferrari");

    ASSERT_EQ(pM.editUser("Mario Rossi", "Luigi Verdi"), 0);
    ASSERT_EQ(pM.editUser("Mario Rossi", "Luigi Verdi"), 1);
    ASSERT_EQ(pM.editUser("Luigi Verdi", "Enzo Ferrari"), 3);
}

TEST(ProgramManager, AddBankAccountTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");

    pM.getByOp();

    ASSERT_EQ(pM.addBankAccount("Mario Rossi", "name"), 0);
    ASSERT_EQ(pM.addBankAccount("Luigi Verdi", "name"), 1);
    ASSERT_EQ(pM.addBankAccount("Mario Rossi", "name"), 4);
}

TEST(ProgramManager, AddTransactionTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addBankAccount("Mario Rossi", "name");

    pM.addTransaction("Mario Rossi", "name", 'D', 80, 1717133339);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getBalance(), 80);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133339).getOperation(), 'D');
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133339).getAmount(), 80);

    // withdrawal
    pM.addTransaction("Mario Rossi", "name", 'W', 30, 1717133340);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getBalance(), 50);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133340).getOperation(), 'W');
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133340).getAmount(), 30);

    // bank transfert
    pM.addUser("Luigi Verdi");
    pM.addBankAccount("Luigi Verdi", "recipient");

    pM.addTransaction("Mario Rossi", "name", 'B', "recipient", 20, 1717133341);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getBalance(), 30);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getAccount(), "recipient");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getRole(), true);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getOperation(), 'B');
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getAmount(), 20);

    ASSERT_EQ(pM.getUser("Luigi Verdi").getAccount("recipient").getBalance(), 20);
    ASSERT_EQ(pM.getUser("Luigi Verdi").getAccount("recipient").getTransaction(1717133341).getAccount(), "name");
    ASSERT_EQ(pM.getUser("Luigi Verdi").getAccount("recipient").getTransaction(1717133341).getRole(), false);
    ASSERT_EQ(pM.getUser("Luigi Verdi").getAccount("recipient").getTransaction(1717133341).getOperation(), 'B');
    ASSERT_EQ(pM.getUser("Luigi Verdi").getAccount("recipient").getTransaction(1717133341).getAmount(), 20);

    // insufficient balance
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "name", 'W', 31, 1717133342), 5);
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "name", 'B', "recipient", 31, 1717133342), 5);

    // not found
    ASSERT_EQ(pM.addTransaction("Enzo Ferrari", "name", 'D', 30, 1717133342), 1); // user not found
    ASSERT_EQ(pM.addTransaction("Enzo Ferrari", "name", 'B', "recipient", 20, 1717133341), 1); // user not found
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "name", 'B', "recipienttttt", 20, 1717133341), 6); // recipient account not found
    ASSERT_EQ(pM.addTransaction("Mario Rossi", "name", 'B', "name", 20, 1717133341), 7); // sender and recipient are the same
}

TEST(ProgramManager, PrintInfoTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addBankAccount("Mario Rossi", "iban1");
    pM.addBankAccount("Mario Rossi", "iban2");

    // print by operation
    ASSERT_EQ(pM.getByOp('D'), 8);
    ASSERT_EQ(pM.getByOp('W'), 8);
    ASSERT_EQ(pM.getByOp('B'), 8);

    pM.addTransaction("Mario Rossi", "iban1", 'D', 50, 1717133341);
    pM.addTransaction("Mario Rossi", "iban1", 'W', 25, 1717133342);
    pM.addTransaction("Mario Rossi", "iban1", 'B', "iban2", 25, 1717133343);
    ASSERT_EQ(pM.getByOp('D'), 0);
    ASSERT_EQ(pM.getByOp('W'), 0);
    ASSERT_EQ(pM.getByOp('B'), 0);

    // print by date
    ASSERT_EQ(pM.getByOp("31/05/2024"), 0);
    ASSERT_EQ(pM.getByOp("35/05/2024"), 9);
    ASSERT_EQ(pM.getByOp("30/05/2024"), 8);
}

TEST(ProgramManager, ClearTransactionsTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addBankAccount("Mario Rossi", "iban1");
    pM.addTransaction("Mario Rossi", "iban1", 'D', 10);
    pM.addBankAccount("Mario Rossi", "iban2");
    pM.addTransaction("Mario Rossi", "iban2", 'D', 10);

    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban1").getTransactions().empty(), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban2").getTransactions().empty(), 0);
    pM.clearTransactions("Mario Rossi", "iban1");
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban1").getTransactions().empty(), 1);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban2").getTransactions().empty(), 0);

    pM.addTransaction("Mario Rossi", "iban1", 'D', 10);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban1").getTransactions().empty(), 0);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban2").getTransactions().empty(), 0);
    pM.clearTransactions();
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban1").getTransactions().empty(), 1);
    ASSERT_EQ(pM.getUser("Mario Rossi").getAccount("iban2").getTransactions().empty(), 1);
}

TEST(ProgramManager, DeleteUserTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");

    ASSERT_EQ(pM.deleteUser("Mario Rossi"), 0);
    ASSERT_EQ(pM.deleteUser("Mario Rossi"), 1);
}

TEST(ProgramManager, DeleteBankAccountTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addBankAccount("Mario Rossi", "name");

    ASSERT_EQ(pM.deleteAccount("Mario Rossi", "name"), 0);
    ASSERT_EQ(pM.deleteAccount("Mario Rossi", "name"), 2);
    ASSERT_EQ(pM.deleteAccount("Luigi Verdi", "name"), 1);
}

TEST(ProgramManager, SaveDataTest) {
    ProgramManager pM;
    pM.addUser("Mario Rossi");
    pM.addBankAccount("Mario Rossi", "name");
    pM.addTransaction("Mario Rossi", "name", 'D', 10, 1717133341);

    pM.saveData();

    ProgramManager pM2;
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getOperation(), 'D');
    ASSERT_EQ(pM2.getUser("Mario Rossi").getAccount("name").getTransaction(1717133341).getAmount(), 10);
    pM2.deleteUser("Mario Rossi");
    pM2.saveData();
}
