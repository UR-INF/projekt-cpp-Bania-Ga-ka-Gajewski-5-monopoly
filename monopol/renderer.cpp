#include "renderer.hpp"
#include "player.hpp"
#include "field.hpp"
#include "propertyfield.hpp"
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

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
    this->renderMessage(fieldToRender->toString());
}

void Renderer::renderMenu(Menu* menuToRender) {
    vector<MenuItem*> currentMenuToRender = menuToRender->getCurrentMenu();

    for(int index = 0; index < currentMenuToRender.size(); index++) {
            cout << index << " - " << currentMenuToRender[index]->getOptionText() << endl;
        }
}

void Renderer::renderBoard(Board* boardToRender) {
    WORD attributes;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    attributes = info.wAttributes;
    for(int index = 0; index < 40; index++) {
        if (index == 1||index == 3) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY );
                this->renderField(boardToRender->getField(index));
        }
        else if (index == 6||index == 8 || index == 9) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 11 || index == 13 || index == 14) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 16 || index == 18 || index == 19) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 21 || index == 23 || index == 24) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED| FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 26 || index == 27 || index == 29) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 31 || index == 32 || index == 34) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 37 || index == 39) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            this->renderField(boardToRender->getField(index));
        }
        else if(index == 2||index == 17||index == 33)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE|BACKGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else if (index == 7 || index == 22 || index == 36)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED| FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            this->renderField(boardToRender->getField(index));
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
            this->renderField(boardToRender->getField(index));
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

