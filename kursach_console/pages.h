#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <windows.h>
#include <sstream>
#include "user.h"
#include "func.h"
#include "games.h"
#include "Bucket.h"
#include <cctype>


class Page {
protected:
    std::string title;
public:
    virtual void Visualisation() {};
    void HandInput(int& CurrentPage) {
        int key = _getch();
        switch (key) {
        case '-1': CurrentPage = -1; break;
        case '1': CurrentPage = 1; break;
        case '2': CurrentPage = 2; break;
        case '3': CurrentPage = -9; break;

        case '0': CurrentPage = -1; break;

        }
    };

    Page(std::string t) : title(t) {};
    virtual ~Page() {};
};



class MainMenu : public Page {
public:
    MainMenu(std::string name) : Page(name) {};
    void Visualisation() override {
        system("cls");
        std::cout << "=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
        std::cout << "1 - Регистрация" << std::endl;
        std::cout << "2 - Вход" << std::endl;
        std::cout << "3 - Вход в админку" << std::endl;
        std::cout << "0 - Выход" << std::endl;

    };
    ~MainMenu() override {};
};



class Registration : protected Page {
public:
    Registration(std::string name) : Page(name) {};
    ~Registration() override {};
    void Visualisation() override {
        system("cls");
        std::string login, password;
        std::cout << "=================================" << std::endl;
        std::cout << "         РЕГИСТРАЦИЯ             " << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Введите логин: " << std::endl;
        std::cin >> login;
        std::cout << "Введите пароль: " << std::endl;
        char ch;
        while ((ch = _getch()) != 13) { // 13 - это Enter
            if (ch == 8) { // Backspace
                if (!password.empty()) {
                    password.pop_back();
                    std::cout << "\b \b";
                }
            }
            else {
                password += ch;
                std::cout << "*";
            }
        }
        currentUser = User(login, password, 0, false);
        std::ofstream outFile("users.data", std::ios::app); //ios::app — добавлять в конец юзерс дата 
        if (outFile.is_open()) {
            outFile << login << "|" << password << "|" << 0 << "|" << 0 << "\n";
            outFile.close();
            std::cout << "\n\nПользователь " << login << " успешно зарегистрирован!";
        }
        else {
            std::cerr << "\n\nОшибка: не удалось открыть файл для записи!";
        }
    };
};

class Login : private Page {
public:

    Login(std::string name) : Page(name) {};
    ~Login() override {};
    void visualisation(int& currentPage, User& CurrentUser) {
        system("cls");
        std::string loginUs, passwordUs;
        std::cout << " -----Вход----- " << std::endl;
        std::cout << " Логин: " << std::endl;
        std::cin >> loginUs;
        std::cout << " Пароль: " << std::endl;
        char ch;
        while ((ch = _getch()) != 13) { // 13 - это Enter
            if (ch == 8) { // Backspace
                if (!passwordUs.empty()) {
                    passwordUs.pop_back();
                    std::cout << "\b \b";
                }
            }
            else {
                passwordUs += ch;
                std::cout << "*";
            }
        }
        User currentUser(loginUs, passwordUs, 0, false);
        if (currentUser.findUser()) {
            currentUser = currentUser.findSettingsUser(loginUs, passwordUs);
            CurrentUser = currentUser;
            std::string usName = currentUser.getName();
            std::cout << std::endl << "\nДобро пожаловать, " << usName << "!" << std::endl;
            Sleep(1000);
            currentPage = 3;
        }
        else {
            std::cout << "\nДанного пользователя не существует " << std::endl;
            Sleep(1400);
            currentPage = 0;
        }

    }

};



/*class Game {
protected:
    std::string name;
    int cost;
    std::string genre;
    bool before18 = true;



public:
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
            outFile << name << "|" << cost << "|" << genre << "|" << before18 << "|" << "\n";
            outFile.close();
            std::cout << "\n\nИгра " << name << " выставлена на продажу!";
        }
        else {
            std::cerr << "\n\nОшибка";
        }
    }

    Game(std::string n, int c, std::string g, bool b18) : name(n), cost(c), genre(g), before18(b18) {};
};*/


class Kabinet : public Page {
public:
    Kabinet(std::string n) : Page(n) {};
    ~Kabinet() override {};
    void visualisation(User& currentUser) {
        system("cls");
        std::cout << "   ЛИЧНЫЙ КАБИНЕТ\n\n ";
        std::cout << "   Пользователь " << currentUser.getName() << std::endl;
        std::cout << "   Ваш баланс: " << currentUser.getBalance() << "p." << std::endl;
        std::cout << std::endl;
        std::cout << "   1 - Перейти к играм" << std::endl;
        std::cout << "   2 - Просмотреть корзину" << std::endl;
        std::cout << "   3 - Пополнить баланс" << std::endl;
        std::cout << "   4 - Выйти из аккаунта" << std::endl;
        std::cout << std::endl;
        std::cout << "   Выберите действие: ";
    };

    void HandInputKabinet(int& CurrentPage) {
        int key = _getch();
        switch (key) {
        case '1': CurrentPage = 4; break;
        case '2': CurrentPage = 7; break;
        case '3': CurrentPage = 5; break;
        case '4': CurrentPage = 6; break;

        }
    };
};


class Popolnenie : public Page {
public:
    Popolnenie(std::string n) : Page(n) {};
    ~Popolnenie() override {};
    void Visualisation() override {
        system("cls");
        std::cout << "   ПОПОЛНЕНИЕ БАЛАНСА\n\n ";
        std::cout << "   Введите сумму пополнения:" << std::endl;
    };
};


class AdminLogin : public Page {
public:
    AdminLogin(std::string n) : Page(n) {};
    ~AdminLogin() override {};
    void visualisation(int& currentPage) {
        system("cls");
        std::string login, password;
        std::cout << "=================================" << std::endl;
        std::cout << "         ВХОД В АДМИНКУ          " << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Введите логин админа: " << std::endl;
        std::cin >> login;
        std::cout << "Введите пароль админа: " << std::endl;
        char ch;
        while ((ch = _getch()) != 13) { // 13 - это Enter
            if (ch == 8) { // Backspace
                if (!password.empty()) {
                    password.pop_back();
                    std::cout << "\b \b";
                }
            }
            else {
                password += ch;
                std::cout << "*";
            }
        }
        if (login == "admin" && password == "admin999") {
            std::cout << "\nВы вошли с правами администратора..." << std::endl;
            Sleep(1400);
            currentPage = -10;
        }
        else {
            std::cout << "\nНеправильно введен логин или пароль, возврат на страницу входа..." << std::endl;
            Sleep(1400);
            currentPage = 0;
        }
    }

};


class AdminMenu : public Page {
public:
    AdminMenu(std::string n) : Page(n) {};
    ~AdminMenu() override {};
    void visualisation() {
        system("cls");
        std::cout << "      ========== ПАНЕЛЬ АДМИНА ========\n ";
        std::cout << std::endl;
        std::cout << "      1 - Добавить игру в список товаров" << std::endl;
        std::cout << "      2 - Изменение пользователей" << std::endl;
        std::cout << "      3 - Удалить игру" << std::endl;
        std::cout << "      4 - Выйти из админки" << std::endl;
        std::cout << std::endl;
        std::cout << "      Выберите действие: ";
    }

    void HandInputAdmin(int& CurrentPage) {
        int key = _getch();
        switch (key) {
        case '1': CurrentPage = -8; break;
        case '2': CurrentPage = -7; break;
        case '3': CurrentPage = -6; break;
        case '4': CurrentPage = 6; break;

        }
    };
};


class GameAddPage : public Page {
public:
    GameAddPage(std::string n) : Page(n) {};
    ~GameAddPage() override {};
    void visualisation() {
        std::string name, genre;
        bool before18;
        int cost, count, id;
        system("cls");
        std::cout << " Введите id: ";
        std::cin >> id;
        std::cout << " Введите название игры: ";
        std::getline(std::cin >> std::ws, name);
        std::cout << std::endl;
        std::cout << " Введите цену: ";
        std::cin >> cost;
        std::cout << std::endl;
        std::cout << " Введите название жанра: ";
        std::getline(std::cin >> std::ws, genre);
        std::cout << std::endl;
        std::cout << " Доступна до 18 лет? (1 или 0): ";
        std::cin >> count;
        (count == 1) ? before18 = true : before18 = false;
        Game gameToAdd(id, name, cost, genre, before18);
        gameToAdd.addGame();

    }
};




class GameDelPage : public Page {
public:
    GameDelPage(std::string n) : Page(n) {};
    ~GameDelPage() override {};
    void visualisation(int &currentPage) {
        int delId;
        system("cls");
        gameShowData();
        std::cout << "\n( 0 - переход назад )" << std::endl;
        std::cout << "\nВведите Id игры для удаления: ";
        std::cin >> delId;
        if (delId == 0) { currentPage = -10; };
        gameDelData(delId);
        
    }
    
};


class UserChangePage : public Page {
public:
    UserChangePage(std::string n) : Page(n) {};
    ~UserChangePage() override {};
    void visualisation() {
        std::string username;
        int operation;
        bool flagChanging = true;
        char YorN;
        system("cls");
        userShowData();
        std::cout << "\nВведите имя пользователя для изменения: ";
        std::getline(std::cin >> std::ws, username);
        while (flagChanging) {
            system("cls");
            if (userExistance(username)) {
                std::cout << "====== Пользователь " << username << " ======";
                std::cout << "\n1 - Изменение имени пользователя ";
                std::cout << "\n2 - Изменение пароля пользователя ";
                std::cout << "\n3 - Изменение баланса пользователя ";
                std::cout << "\n4 - Изменение прав пользователя ";
                std::cout << "\n5 - Удаление пользователя ";
                std::cout << "\n6 - Отмена действия";
                std::cout << "\n\nВведите номер операции изменения: ";
                std::cin >> operation;
                userChangeData(username, operation);
                Sleep(1300);
                if (operation != 6 && operation != 5) {
                    std::cout << "\nПродолжить изменение пользователя " << username << "? (y/n)";
                    std::cin >> YorN;
                    YorN = tolower(YorN);
                    if (YorN == 'y' || YorN == 'н') {
                        continue;
                    }
                    if (YorN == 'n' || YorN == 'т') {
                        flagChanging = false;
                        break;
                    }
                }
                else {
                    return;
                }
            }
            else {
                std::cout << "\nДанного пользователя не существует"; 
                Sleep(1300);
                return;
            }
        }
    }
};




class GamesWindow : public Page {
public:
    GamesWindow(std::string n) : Page(n) {};
    void visualisation() {
        system("cls");
        std::cout << "=================================== КАТАЛОГ ИГР ===================================\n" << std::endl;
        gameShowData(); 
    }
};


class BucketWindow : public Page {

public:
    BucketWindow(std::string n) : Page(n) {};
    /*void visualisation(Bucket& bucket) {
        int choose;
        std::cout << "\nОбщая стоимость игр: "  << bucket.getTotalPrice();
        std::cout << "\n1 - Оформить покупку игр";
        std::cout << "\n2 - Убрать игру из корзины";
        std::cout << "\n0 - Назад";
        std::cin >> choose;
        if (choose == 1) {
            if()
        }
    }*/
};
