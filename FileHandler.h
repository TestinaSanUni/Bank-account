//
// Created by Testa on 5/26/2024.
//

#ifndef BANK_ACCOUNT_FILEHANDLER_H
#define BANK_ACCOUNT_FILEHANDLER_H
#include <fstream>
#include <list>
using namespace std;


class FileHandler {
public:
    FileHandler() = default;
    void loadUsers(list<string>& list); // open the files and load the data structures on memory
    void saveUsers(const list<string>& list); // update files and release allocated memory

private:
    fstream fileReader;
    fstream fileWriter;
};


#endif //BANK_ACCOUNT_FILEHANDLER_H
