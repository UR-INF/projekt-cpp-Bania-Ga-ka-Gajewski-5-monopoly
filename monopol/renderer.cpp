#include "renderer.hpp"
#include "player.hpp"
#include "field.hpp"
#include "propertyfield.hpp"

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

void Renderer::renderField(Field* fieldToRender) {    
    string fieldNumber = to_string(fieldToRender->getFieldNumber());

    switch(fieldToRender->getFieldType()) {
        case START:
            this->renderMessage(fieldNumber + " - Pole typu START");
            break;
        case JAIL:
            this->renderMessage(fieldNumber + " - Pole wiezienia");
            break;
        case GO_TO_JAIL:
            this->renderMessage(fieldNumber + " - Pole idziesz do wiezienia");
            break;
        case FREE_PARKING:
            this->renderMessage(fieldNumber + " - Pole darmowy parking");
            break;
        case PROPERTY:
            {
                PropertyField* propertyField = static_cast<PropertyField*>(fieldToRender);
                this->renderMessage(fieldNumber + " - Pole nieruchomosci - " + propertyField->getPropertyInfo());
                break; 
            }            
        case RAILWAY:
            this->renderMessage(fieldNumber + " - Pole koleje");
            break;
        case ELECTRICITY:
            this->renderMessage(fieldNumber + " - Pole elektrownia");
            break;
        case WATER_SUPPLY_NETWORK:
            this->renderMessage(fieldNumber + " - Pole wodociagi");
            break;
        case INCOME_TAX:
            this->renderMessage(fieldNumber + " - Pole podatek dochodowy");
            break;
        case BLUE_CHANCE:
            this->renderMessage(fieldNumber + " - Pole szansy - niebieska");
            break;
        case RED_CHANCE:
            this->renderMessage(fieldNumber + " - Pole szansy - czerwona");
            break;
        case LUXURY_TAX:
            this->renderMessage(fieldNumber + " - Pole podatek od luksusu");
            break;
    }
}

void Renderer::renderMenu(Menu* menuToRender) {
    vector<MenuItem*> currentMenuToRender = menuToRender->getCurrentMenu();

    for(int index = 0; index < currentMenuToRender.size(); index++) {
            cout << index << " - " << currentMenuToRender[index]->getOptionText() << endl;
        }
}

void Renderer::renderBoard(Board* boardToRender) {
    for(int index = 0; index < 40; index++) {
        this->renderField(boardToRender->getField(index));
    }
}