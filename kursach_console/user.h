#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class User {
protected:
    std::string name;
    std::string password;
    int balance;
    bool isAdmin = false;



public:
    void show() {
        std::cout << "\n-------------------------------\n";
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Баланс:     " << balance << "$" << std::endl;
        if (isAdmin) { std::cout << "Доступны права админа"; };
        if (!isAdmin) { std::cout << "Отсутствуют права администратора"; };
        std::cout << "\n-------------------------------";
    };

    bool findUser() {
        std::ifstream Datafile("users.data");
        if (Datafile.is_open()) {
            std::string line;
            while (getline(Datafile, line)) {
                std::string login1, password1;
                int i = 0;

                //Читаем логин до первого |
                for (; i < line.length(); i++) {
                    if (line[i] == '|') break;
                    login1 += line[i];
                }
                //Пропускаем | между логином и паролем
                while (i < line.length() && line[i] == '|') {
                    i++;
                }
                while (i < line.length() && line[i] != '|') {
                    password1 += line[i];
                    i++;
                }
                if (name == login1 && password == password1) {
                    return true;
                }
            }
            return false;
        };
    };


    static User findSettingsUser(std::string loginUs, std::string passUs) {
        std::ifstream Datafile("users.data");
        std::string line;

        if (Datafile.is_open()) {
            while (std::getline(Datafile, line)) {
                std::stringstream ss(line);
                std::string currentLogin, password, balanceStr, isAdminStr;
                std::getline(ss, currentLogin, '|');
                std::getline(ss, password, '|');
                std::getline(ss, balanceStr, '|');
                std::getline(ss, isAdminStr, '|');
                int balance = std::stod(balanceStr);
                bool isAdmin = std::stoi(isAdminStr);
                    if (currentLogin == loginUs && password == passUs) {
                        return User(currentLogin, password, balance, isAdmin);
                    }
                
            }
        }

        return User("", "", 0, false);
    };


    std::string getName() {
        return name;
    };

    double getBalance() {
        return balance;
    };

    bool getIsAdmin() {
        return isAdmin;
    };
    std::string getPassword() {
        return password;
    };


    void setBalance(int bal) {
        balance = bal;

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
                std::string currentLogin;
                ss >> currentLogin;
                if (currentLogin == name) {
                    std::string password, isAdmin;
                    int oldBalance;
                    ss >> password >> oldBalance >> isAdmin;   
                    dataLines[i] = currentLogin + " " + password + " " + std::to_string(bal) + " " + isAdmin;
                    break;
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

    User(std::string n, std::string p, int b, bool isA) : name(n), password(p), balance(b), isAdmin(isA) {};

    User() { name = ""; password = ""; balance = 0; isAdmin = false; };
    ~User() {};
};


extern User currentUser;