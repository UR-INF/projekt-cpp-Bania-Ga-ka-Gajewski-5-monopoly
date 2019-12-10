
#include "menu.hpp"
#include "menuitem.hpp"
#include "player.hpp"
#include "actiontype.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Menu::Menu() {
    this->allMenuItems.push_back(new MenuItem("Rzut kostkami", NORMAL_DICE_ROLL)); // 0
    this->allMenuItems.push_back(new MenuItem("Pozyczka z banku", TAKE_LOAN)); // 1
    this->allMenuItems.push_back(new MenuItem("Splata pozyczki", PAY_LOAN)); // 2
    this->allMenuItems.push_back(new MenuItem("Kupno domku", BUY_HOUSE)); // 3
    this->allMenuItems.push_back(new MenuItem("Sprzedaz domku", SELL_HOUSE)); // 4
    this->allMenuItems.push_back(new MenuItem("Wymiana", EXCHANGE)); // 5
    this->allMenuItems.push_back(new MenuItem("Rzut kostkami na wyjscie z wiezienia", OUT_OF_JAIL_ROLL_DICE)); // 6
    this->allMenuItems.push_back(new MenuItem("Uzycie karty wyjscie z wiezienia", USE_CARD_TO_GET_FREE)); // 7
    this->allMenuItems.push_back(new MenuItem("Zaplac 50$ i rzuc kostkami", PAY_AND_GET_FREE)); // 8
    this->allMenuItems.push_back(new MenuItem("Tak", CONFIRM)); // 9
    this->allMenuItems.push_back(new MenuItem("Anuluj", CANCEL)); // 10
    this->allMenuItems.push_back(new MenuItem("Wyswietl plansze", SHOW_BOARD)); // 11
}

Menu::~Menu() {
    // std::cout << "Usuwam obiekt Menu" << endl;
    this->allMenuItems.clear();
    this->currentMenu.clear();
}

vector<MenuItem*> Menu::getCurrentMenu() {
    return this->currentMenu;
}

void Menu::construct(Player* player) {
    this->currentMenu.clear();

    if(player->isInJail()) {
        this->currentMenu.push_back(this->allMenuItems[6]);

        if(player->hasOutOfJailCard()) {
            this->currentMenu.push_back(this->allMenuItems[7]);
        }        
        
        if(player->isSolvent(50, true)) {
            this->currentMenu.push_back(this->allMenuItems[8]);
        }

        if(player->hasActiveLoan()) {
            if (player->isSolvent(500, true)  && player->getCanPayLoan()) {
                this->currentMenu.push_back(this->allMenuItems[2]);
            }
        }      
    }
    else {
        this->currentMenu.push_back(this->allMenuItems[0]);
        // this->currentMenu.push_back(this->allMenuItems[5]);  

        if (player->hasAnyCountry()) {
            this->currentMenu.push_back(this->allMenuItems[3]);
            this->currentMenu.push_back(this->allMenuItems[4]);
        }              

        if(player->hasActiveLoan()) {
            if (player->isSolvent(500, true)  && player->getCanPayLoan()) {
                this->currentMenu.push_back(this->allMenuItems[2]);
            }
        }
        else {
            this->currentMenu.push_back(this->allMenuItems[1]);
        }
    }

    this->currentMenu.push_back(this->allMenuItems[11]);
    
    cout << endl;
}

void Menu::constructConfirm() {
    this->currentMenu.clear();

    this->currentMenu.push_back(this->allMenuItems[9]);
    this->currentMenu.push_back(this->allMenuItems[10]);

    cout << endl;
}