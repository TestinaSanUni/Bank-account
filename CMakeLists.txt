cmake_minimum_required(VERSION 3.27)
project(Bank_account)

set(CMAKE_CXX_STANDARD 11)

add_executable(Bank_account main.cpp)
set(SOURCE_FILES User.cpp
        User.h
        BankAccount.cpp
        BankAccount.h
        Transaction.cpp
        Transaction.h
        FileHandler.cpp
        FileHandler.h
        ProgramManager.cpp
        ProgramManager.h)
add_library(core ${SOURCE_FILES})
target_link_libraries(Bank_account core)

add_subdirectory(test)
