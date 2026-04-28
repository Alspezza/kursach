#include <iostream>
#include <string>
#include <conio.h>
#include "user.h"
#include "func.h"
#include "pages.h"
#include "Bucket.h"

User currentUser;
Bucket currentBucket;


int main() {
    User Admin("admin", "admin999", 999999, true);
    setlocale(LC_ALL, "RU");
    int currentPage = 0;
    User currentUser;
    int balPopolnenie, balUser;

    while (true) {
        if (currentPage == 0) {
            MainMenu MAINMENU("Главное меню");
            MAINMENU.Visualisation();
            MAINMENU.HandInput(currentPage);

        }
        else if (currentPage == 1) {
            Registration RegPage("Страница регистрации");
            RegPage.Visualisation();
            Sleep(1300);
            currentPage = 0;
            std::fstream file("users.data");
            if (file.is_open()) {
                std::string line;
                while (getline(file, line)) {
                    std::cout << line;
                }
            }
        }
        else if (currentPage == 2) {
            Login LoginPage("Вход");
            LoginPage.visualisation(currentPage, currentUser);

        }
        else if (currentPage == 3) {
            Kabinet KabinetPage("Личный кабинет");
            KabinetPage.visualisation(currentUser);
            KabinetPage.HandInputKabinet(currentPage);
            
        }
        else if (currentPage == 4) {
            int gameId;
            GamesWindow catalog("Каталог игр");
            catalog.visualisation();
            std::cout << "\nВведите номер игры для добавления в корзину: ";
            std::cout << "\n0 - переход назад";
            std::cout << std::endl;
            std::cin >> gameId;
            if (gameId == 0) {
                currentPage = 3;
            }
            else if (gameExistance(gameId) && gameId != 0) {
                Game thisGame = findGameById(gameId);
                currentBucket.addGame(thisGame);
                std::cout << "\n" << thisGame.getName() << " добавлена в корзину...";
                Sleep(1400);
            }
            else {
                std::cout << "\nДанной игры не существует.";
                Sleep(1400);
            }
            
        }
        else if (currentPage == 5) {
            Popolnenie PopolneniePage("Страница пополнения баланса");
            PopolneniePage.Visualisation();
            std::cin >> balPopolnenie;
            balUser = currentUser.getBalance();
            balUser += balPopolnenie;
            currentUser.setBalance(balUser);
            updateUserData(currentUser.getName(), balUser);
            std::cout << "Баланс успешно пополнен, переход в личный кабинет..." << std::endl;
            Sleep(1400);
            currentPage = 3;

        }
        else if (currentPage == 6) {
            User defUser("", "", 0, false);
            currentUser = defUser;
            std::cout << "\nВы вышли из аккаунта, перенос на главную страницу..." << std::endl;
            Sleep(1400);
            currentPage = 0;
        }
        else if (currentPage == 7) {
            BucketWindow bucketWindow("Страница корзины");
            system("cls");
            std::cout << "=================================== КОРЗИНА ПОЛЬЗОВАТЕЛЯ " << currentUser.getName() << " ===================================\n" << std::endl;
            currentBucket.showGames();
            std::cout << "Баланс пользователя: " << currentUser.getBalance();
            std::cout << "\nОбщая стоимость игр: " << currentBucket.getTotalPrice();
            std::cout << "\n\n1 - Оформить покупку игр";
            std::cout << "\n2 - Убрать игру из корзины";
            std::cout << "\n0 - Назад ";
            std::cout << std::endl;
            char choose = _getch();
            if (choose == '1') {
                if (currentUser.getBalance() > currentBucket.getTotalPrice() || currentUser.getBalance() == currentBucket.getTotalPrice()) {
                    int changeBAL = currentUser.getBalance() - currentBucket.getTotalPrice();
                    currentUser.setBalance(changeBAL);
                    int minusBal = currentBucket.getTotalPrice();
                    updateUserData(currentUser.getName(), changeBAL);
                    currentBucket.clear();
                    std::cout << "\nИгры успешно куплены, с баланса списано: " << minusBal << "р.";
                    Sleep(1400);
                    currentPage = 3;
                }
                else {
                    std::cout << "\nНе хватает средств на покупку, измените содержимое корзины или пополните баланс...";
                    Sleep(1400);
                }
            }
            if (choose == '2') {
                std::cout << "\nВведите номер игры для удаления";
                char num = _getch();
                for (const Game&g : currentBucket.games) {
                    if (g.id == num) {
                        int intnum = num - '0';
                        currentBucket.delGame(intnum);
                    }
                }
                std::cout << "Игра удалена из корзины";
                Sleep(1400);
                currentPage = 3;
            }
            if (choose == '0') {
                currentPage = 3;
            }
        }
        else if (currentPage == -1) {
            std::cout << "Вы вышли из программы." << std::endl;
            break;
        }
        else if (currentPage == -6) {
            GameDelPage gameDelPage("Страница удаление игры");
            gameDelPage.visualisation(currentPage);
        }
        else if (currentPage == -7) {
            UserChangePage userChangePage("Страница изменения пользователей");
            userChangePage.visualisation();
            std::cout << "Пользователь успешно изменен\n";
            currentPage = -10;
            
        }
        else if (currentPage == -8) {
            GameAddPage addGame("Страница добавления игры");
            addGame.visualisation();
            currentPage = -10;
        }
        else if (currentPage == -9) {
            AdminLogin adminLogin("Вход в админку");
            adminLogin.visualisation(currentPage);
        }
        else if (currentPage == -10) {
            currentUser = Admin;
            AdminMenu adminMenu("Панель управления админа");
            adminMenu.visualisation();
            adminMenu.HandInputAdmin(currentPage);

        }

           
    }
}


