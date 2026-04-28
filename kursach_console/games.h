#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Game {

public:
    int id;
    std::string name;
    int cost;
    std::string genre;
    bool before18 = true;




    void show() {
        std::cout << "\n-------------------------------\n";
        std::cout << "Название: " << name << std::endl;
        std::cout << "Цена:     " << cost << "$" << std::endl;
        std::cout << "Жанр:     " << genre << std::endl;
        if (before18) { std::cout << "Без возрастного ограничения"; };
        if (!before18) { std::cout << "18+"; };
        std::cout << "\n-------------------------------";
    };

    void addGame() {
        std::ofstream outFile("games.data", std::ios::app); //ios::app — добавлять в конец гейис дата 
        if (outFile.is_open()) {
            outFile << id << "|" << name << "|" << cost << "|" << genre << "|" << before18 << "|" << "\n";
            outFile.close();
            std::cout << "\n\nИгра " << name << " выставлена на продажу!";
        }
        else {
            std::cerr << "\n\nОшибка";
        }
    }

    Game(int i,std::string n, int c, std::string g, bool b18) : id(i), name(n), cost(c), genre(g), before18(b18) {};

    int getId() {
        return id;
    }
    std::string getName() {
        return name;
    };
    int getCost() {
        return cost;
    }
    std::string getGenre() {
        return genre;
    }
    bool isBefore18() {
        return before18;
    }
};