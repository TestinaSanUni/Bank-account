//
// Created by Testa on 5/26/2024.
//

#include "FileHandler.h"
#include <iostream>

//
// Public methods
//

list<User> FileHandler::loadData() {
    fileReader.open("Users.txt");
    list<User> users;

    if(fileReader.is_open()) {
        cout << "Il file si e' aperto correttamente" << endl;

        do {
            User newUser(readWord(), readWord());
            users.push_back(newUser);
        } while(!fileReader.eof());

        fileReader.close();
    }

    return users;
}

void FileHandler::saveData(const list<User>& list) {
    fileWriter.open("Users.txt");

    if(fileWriter.is_open()) {
        const User& user = list.front();
        fileWriter << user.getName() << " " << user.getSurname();

        bool firstElement = true; // skip the first element of the list. It has already been printed differently
        for(const User& i : list)
            if(firstElement) firstElement = false;
            else fileWriter << endl << i.getName() << " " << i.getSurname();

        fileWriter.close();
    }
}


//
// Private methods
//

string FileHandler::readWord() {
    string word;
    char character = fileReader.get();

    while(character != ' ' && character != '\n' && !fileReader.eof()) {
        word += character;
        character = fileReader.get();
    }

    return word;
}