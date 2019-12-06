#include "player.hpp"
#include "menuitem.hpp"
#include <string>
#include <vector>

#ifndef MENU_HPP
#define MENU_HPP

using namespace std;

class Menu {
    private:
        vector<MenuItem*> allMenuItems;
        vector<MenuItem*> currentMenu;

    public:
        Menu();
        ~Menu();
        void construct(Player* player);
        void constructConfirm();
        vector<MenuItem*> getCurrentMenu();
};

#endif