#include "player.hpp"
#include "diceroller.hpp"
#include "board.hpp"
#include <vector>
#include <map>

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
        std::map<int, Player*> orderOfMoves;
        int playerPositions[];       

    
    public:
        GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers);
        ~GameController();
        void start();
        void setPlayersOnStart();
        void nextPlayer();
        bool doesSomeoneWin();
        void performAction();
        std::map<int, Player*> setPlayersMoveOrder(); 

};

#endif