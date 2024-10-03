project(test)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run RunAllTests.cpp
        FileHandlerTest.cpp
        UserTest.cpp
        BankAccountTest.cpp
        TransactionTest.cpp
        ProgramManagerTest.cpp
)

target_link_libraries(Google_Tests_run gtest gtest_main core)