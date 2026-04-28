#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include "games.h"


auto findGameById(int id) {
    std::ifstream infile("games.data");
    std::vector<std::string> dataLines;
    if (infile.is_open()) {
        std::string line;
        bool find = false;
        while (std::getline(infile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string currentName, strId, strCost, strGenre, strBefore18;
            int cost, ident;
            bool before18;
            std::getline(ss, strId, '|');
            ident = std::stoi(strId);
            std::getline(ss, currentName, '|');
            std::getline(ss, strCost, '|');
            cost = std::stoi(strCost);
            std::getline(ss, strGenre, '|');
            std::getline(ss, strBefore18, '|');
            before18 = std::stoi(strBefore18);
            if (ident == id) {
                
                return Game(id, currentName, cost, strGenre, before18);
            }
        }
    }
}




bool gameExistance(int id) {
    std::ifstream infile("games.data");
    std::vector<std::string> dataLines;
    if (infile.is_open()) {
        std::string line;
        bool find = false;
        while (std::getline(infile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string currentName, strId;
            std::getline(ss, strId, '|');
            int Id = std::stoi(strId);
            if (Id == id) {
                find = true;
                return true;
            }
        }
    }
    return false;
}

bool userExistance(std::string Name) {
    std::ifstream infile("users.data");
    std::vector<std::string> dataLines;
    if (infile.is_open()) {
        std::string line;
        bool find = false;
        while (std::getline(infile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string currentName;
            std::getline(ss, currentName, '|');
            if (currentName == Name) {
                find = true;
                return true;
            }
        }
    }
    return false;
}





void userDelData(std::string delName) {
    std::ifstream infile("users.data");
    std::vector<std::string> dataLines;
    if (infile.is_open()) {
        std::string line, deletedName;
        bool find = false;
        while (std::getline(infile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string currentName;
            std::getline(ss, currentName, '|');
            if (currentName == delName) {
                dataLines.erase(dataLines.begin() + i);
                find = true;
                deletedName = currentName;
                break;
            }
        }
        if (find) {
            std::cout << "\nПользователь " << deletedName << " успешно удален" << std::endl;
        }
        else {
            std::cout << "\nОшибка, пользователь " << deletedName << " не найден" << std::endl;
            infile.close();
            return;
        }
        std::ofstream outfile("users.data", std::ios::trunc);
        for (int i = 0; i < dataLines.size(); i++) {
            outfile << dataLines[i] << std::endl;
        }
        outfile.close();
    }
    infile.close();
}





void userChangeData(std::string chanName, int operation) {     //(int operation) 1 - менять имя, 2 - менять пароль, 3 - менять баланс, 4 - менять права админа
    std::ifstream infile("users.data");
    std::vector<std::string> dataLines;
    std::string chName, chPass, chBal, chIsAdmin, Name, Pass, Bal, IsAdmin, newLine;
    if (infile.is_open()) {
        bool find = false;
        std::string line;
        while (std::getline(infile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string name, pass, bal, isAdmin;
            std::getline(ss, name, '|');
            if (name == chanName) {
                std::getline(ss, pass, '|');
                std::getline(ss, bal, '|');
                std::getline(ss, isAdmin, '|');
                find = true;
                chName = name;
                chPass = pass;
                chBal = bal; 
                chIsAdmin = isAdmin;
                dataLines.erase(dataLines.begin() + i);
                break;
            }
        }
        /*if (find) {
            //std::cout << "\nПользователь " << chanName << " успешно изменен" << std::endl;
        }
        else {
            std::cout << "\nОшибка, пользователь " << chanName << " не найден" << std::endl;
            infile.close();
            return;
        }*/
        switch (operation) {
            case 1:
                std::cout << "\nВведите новое имя пользователя: ";
                std::getline(std::cin >> std::ws, Name);
                newLine = Name + "|" + chPass + "|" + chBal + "|" + chIsAdmin;
                dataLines.push_back(newLine);
                break;
            case 2:
                std::cout << "\nВведите новый пароль: ";
                std::getline(std::cin >> std::ws, Pass);
                newLine = chName + "|" + Pass + "|" + chBal + "|" + chIsAdmin;
                dataLines.push_back(newLine);
                break;
            case 3:
                std::cout << "\nВведите новый баланс: ";
                std::getline(std::cin >> std::ws, Bal);
                newLine = chName + "|" + chPass + "|" + Bal + "|" + chIsAdmin;
                dataLines.push_back(newLine);
                break;
            case 4:
                std::cout << "\nДавать доступ к правам администратора? (1/0)  ";
                std::getline(std::cin >> std::ws, IsAdmin);
                newLine = chName + "|" + chPass + "|" + chBal + "|" + IsAdmin;
                dataLines.push_back(newLine);
                break;
            case 5:
                char chr;
                std::cout << "\nВы уверены что хотите удалить этого пользователя? (y/n)";
                std::cin >> chr;
                chr = tolower(chr);
                if (chr == 'y') {
                    userDelData(chanName);
                    break;
                }
                if (chr == 'n') {
                    std::cout << "\nУдаление пользователя отменено.";
                    break;
                }

            case 6:
                std::cout << "\nИзменение пользователя " << chanName << " отменено...";
                return;
        }
        std::ofstream outfile("users.data", std::ios::trunc);
        for (int i = 0; i < dataLines.size(); i++) {
            outfile << dataLines[i] << std::endl;
        }
        outfile.close();
    }
    infile.close();
};




void userShowData() {
    std::ifstream inFile("users.data");
    std::vector<std::string> GameLines;
    int count = 1;
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                GameLines.push_back(line);
            }
        }
        inFile.close();

        for (int i = 0; i < GameLines.size(); i++) {
            std::stringstream ss(GameLines[i]);
            std::string name, password, strBal, strIsAdmin;
            std::getline(ss, name, '|');

            std::getline(ss, password, '|');

            std::getline(ss, strBal, '|');

            std::getline(ss, strIsAdmin, '|');

            std::cout << std::left
                << std::setw(3) << count
                << "| " << std::setw(15) << name
                << "| " << std::setw(15) << password
                << "| " << std::setw(8) << strBal << " |" << std::endl;
            count++;
        }
    }
};



void gameShowData() {
    std::ifstream inFile("games.data");
    std::vector<std::string> GameLines;
    int count = 1;
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                GameLines.push_back(line);
            }
        }
        inFile.close();

        for (int i = 0; i < GameLines.size(); i++) {
            std::stringstream ss(GameLines[i]);
            std::string name, genre, strCost, strBefore18, before18, strId;
            int cost;
            std::getline(ss, strId, '|');

            std::getline(ss, name, '|');

            std::getline(ss, strCost, '|');
            cost = std::stoi(strCost);

            std::getline(ss, genre, '|');

            std::getline(ss, strBefore18, '|');
            if (strBefore18 == "1") {
                before18 = "Без возрастного ограничения";
            }
            else {
                before18 = "18+";
            }

            std::cout << std::left 
                << "| " << std::setw(2) << strId
                << "| " << std::setw(25) << name
                << "| " << std::setw(8) << cost
                << "| " << std::setw(12) << genre
                << "| " << std::setw(30) << before18 << " |" << std::endl;
            count++;
        }
    }
};




void gameDelData(int delId) {
    std::ifstream infile("games.data");
    std::vector<std::string> dataLines;
    if (infile.is_open()) {
        std::string line, deletedName;
        bool find = false;
        while (std::getline(infile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string currentName, currentStrId;
            int currentId;
            std::getline(ss, currentStrId, '|');
            currentId = std::stoi(currentStrId);
            std::getline(ss, currentName, '|');
            if (currentId == delId) {
                dataLines.erase(dataLines.begin() + i);
                find = true;
                deletedName = currentName;
                break;
            }
        }
        if (find) {
            std::cout << "\nИгра " << deletedName << " успешно удалена" << std::endl;
        }
        else {
            std::cout << "\nОшибка, игра " << deletedName << " не найдена" << std::endl;
            infile.close();
            return;
        }
        std::ofstream outfile("games.data", std::ios::trunc);
        for (int i = 0; i < dataLines.size(); i++) {
            outfile << dataLines[i] << std::endl;
        }
        outfile.close();
    }
    infile.close();
};



void updateUserData(std::string UserLogin, int NewUserBalance) {
    std::ifstream inFile("users.data");
    std::vector<std::string> dataLines;
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                dataLines.push_back(line);
            }
        }
        inFile.close();

        for (int i = 0; i < dataLines.size(); i++) {
            std::stringstream ss(dataLines[i]);
            std::string currentLogin, password, strBalance ,isAdmin;;
            std::getline(ss, currentLogin, '|');
            std::getline(ss, password, '|');
            std::getline(ss, strBalance, '|');
            std::getline(ss, isAdmin, '|');
            if (currentLogin == UserLogin) {
                dataLines[i] = currentLogin + "|" + password + "|" + std::to_string(NewUserBalance) + "|" + isAdmin;
            }
        }
        std::ofstream outFile("users.data", std::ios::trunc); //trunc очистит файл перед записью
        if (outFile.is_open()) {
            for (const auto& updatedLine : dataLines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();
        }
    }
}