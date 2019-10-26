#include "player.hpp"
#include "diceroller.hpp"
#include <vector>

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {
    private:
        int board; // tu bedzie obiekt planszy
        DiceRoller* diceRoller;
        int numberOfPlayers;
        int numberOfActivePlayers; // liczba graczy która jest w rozgrywce, nie-bankruci
        std::vector<Player> players;
        Player* currentPlayer;
        int playerPositions[];


    
    public:
        GameController();
        ~GameController();
        void start();
        void setPlayersOnStart();
        void nextPlayer();
        bool doesSomeoneWin();
        void performAction();
        std::vector<Player> setPlayersOrder(); 

};

#endif