#include "player.hpp"
#include <string>
#include <vector>

#ifndef MENU_HPP
#define MENU_HPP

using namespace std;

class Menu {
    private:
        vector<string> freedomOptions;
        vector<string> jailOptions;
        int choosedOption;

    public:
        Menu();
        ~Menu();
        void render(Player* player);
        int getChoosedOption();
};

#endif