cmake_minimum_required(VERSION 3.27)
project(Bank_account)

set(CMAKE_CXX_STANDARD 11)

add_executable(Bank_account main.cpp
        User.cpp
        User.h
        BankAccount.cpp
        BankAccount.h
        Transaction.cpp
        Transaction.h
        FileHandler.cpp
        FileHandler.h)
