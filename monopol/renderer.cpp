#include "renderer.hpp"
#include "player.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::renderMessage(string message) {
    cout << message << endl;
}

void Renderer::renderCurrentPlayer(Player* playerToRender) {
    this->renderMessage("Ruch gracza: " + playerToRender->getName());
    cout << "Stan konta: " << playerToRender->getPlayerState().getMoney() << endl;
    cout << endl;
}

void Renderer::renderPlayersMoveOrder(vector<Player> moveOrderToRender) {
    this->renderMessage("Gracze wykonuja ruch w kolejnosci: ");
   
    for(vector<Player>::iterator it = moveOrderToRender.begin(); it != moveOrderToRender.end(); ++it) {
        this->renderMessage(it->getName());
    }

    cout << endl;
}

void Renderer::renderPlayerPositions(vector<Player> playersToRender) {
    for(vector<Player>::iterator it = playersToRender.begin(); it != playersToRender.end(); ++it) {
        cout << "Gracz " << it->getName() 
             << " jest na polu " << it->getPosition() 
             << endl;
    }
    
    cout << endl;
}

void Renderer::renderMenu(Menu* menuToRender) {
    vector<MenuItem*> currentMenuToRender = menuToRender->getCurrentMenu();

    for(int index = 0; index < currentMenuToRender.size(); index++) {
            cout << index << " - " << currentMenuToRender[index]->getOptionText() << endl;
        }
}