#include "player.hpp"
#include "diceroller.hpp"
#include "board.hpp"
#include <vector>

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {
    private:
        Board* board; // tu bedzie obiekt planszy
        DiceRoller* diceRoller;
        int numberOfPlayers;
        int numberOfActivePlayers; // liczba graczy która jest w rozgrywce, nie-bankruci
        std::vector<Player> players;
        Player* currentPlayer;
        std::vector<Player> orderOfMoves;   

    
    public:
        GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers);
        ~GameController();
        void init();
        void start();
        void setPlayersOnStart();
        void nextPlayer();
        bool doesSomeoneWin();
        void performAction();
        void setPlayersMoveOrder();
        void renderPlayersMoveOrder();
        void renderPlayersPositions(); 
        void renderCurrentPlayer();

};

#endif