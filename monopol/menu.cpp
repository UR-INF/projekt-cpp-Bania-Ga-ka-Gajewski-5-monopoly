
#include "menu.hpp"
#include "player.hpp"
#include <iostream>

Menu::Menu() {
    this->freedomOptions.push_back("Rzut kostkami");
    this->freedomOptions.push_back("Zakup domkow");
    this->freedomOptions.push_back("Wymiana z innym graczem");
    this->freedomOptions.push_back("Pozyczka od banku");

    this->jailOptions.push_back("Rzut kostkami na wyjscie z wiezienia");
    this->jailOptions.push_back("Uzycie karty wyjscie z wiezienia");
    this->jailOptions.push_back("Zaplata 50$ i rzut kostkami");
}

Menu::~Menu() {
    std::cout << "Usuwam obiekt Menu" << endl;
    this->freedomOptions.clear();
    this->jailOptions.clear();
}

void Menu::render(Player* player) {
    if (player->isInJail()) {
        for(int index = 0; index < this->jailOptions.size(); index++) {
            cout << index << " - " << this->jailOptions[index] << endl;
        }
    }
    else {
        for(int index = 0; index < this->freedomOptions.size(); index++) {
            cout << index << " - " << this->freedomOptions[index] << endl;
        }
    }    
    
    cout << endl;
}