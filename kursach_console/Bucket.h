#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include "games.h"

class Bucket {
    

public:
    std::vector<Game> games;
    void clear() {
        games.clear();
    }

    void showGames() {
        if (games.empty()) {
            std::cout << "\nКорзина пуста \n\n";
            return; 
        }
        for (Game& game : games) {
            std::string strBefore18;
            if (game.isBefore18()) {
                strBefore18 = "Без возрастного ограничения";
            }
            else {
                strBefore18 = "18+";
            }

            std::cout << std::left
                << "| " << std::setw(2) << game.getId()
                << "| " << std::setw(25) << game.getName()
                << "| " << std::setw(8) << game.getCost()
                << "| " << std::setw(12) << game.getGenre()
                << "| " << std::setw(30) << strBefore18 << " |" << std::endl;
        }
    }

    void addGame(const Game& game) {
        for (auto& item : games) {
            if (item.name == game.name) {
                std::cout << "\nИгра уже в корзине";
                return;
            }
        }
        games.push_back(game);
    }

    void delGame(int productId) {
        for (auto i = games.begin(); i != games.end(); ++i) {
            if (i->id == productId) { 
                games.erase(i);       
                break;
            }
        }
    }

    
    double getTotalPrice() const {
        return std::accumulate(games.begin(), games.end(), 0.0,
            [](double sum, const Game& item) {
                return sum + item.cost;
            });
    }

};