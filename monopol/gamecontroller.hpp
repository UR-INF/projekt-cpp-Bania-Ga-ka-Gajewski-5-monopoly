#include "player.hpp"
#include "diceroller.hpp"
#include "board.hpp"
#include "menu.hpp"
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
        Menu* menu;

    
    public:
        GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers, Menu* menu);
        ~GameController();
        void init();
        void start();
        void setPlayersOnStart();
        void nextPlayer();
        bool doesSomeoneWin();
        void performAction();
        void takeLoan(Player* player);
        void simpleDiceRoll();
        void normalDiceRoll();
        void getOutFromJailDiceRoll();
        void setPlayersMoveOrder();
        void bankruptPlayer(Player* player);
        void renderPlayersMoveOrder();
        void renderPlayersPositions(); 
        void renderCurrentPlayer();
        void renderMessage(string message);

		void pickBlueCard(Player* player);
		void pickRedCard(Player* player);
};

#endif