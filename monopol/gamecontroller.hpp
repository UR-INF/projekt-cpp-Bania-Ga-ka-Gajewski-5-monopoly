#include "player.hpp"
#include "diceroller.hpp"
#include "board.hpp"
#include "menu.hpp"
#include "renderer.hpp"
#include "purchasablefield.hpp"
#include <vector>

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {
    private:
        Board* board; // tu bedzie obiekt planszy
        DiceRoller* diceRoller;
        Renderer* renderer;
        int numberOfPlayers;
        int numberOfActivePlayers; // liczba graczy która jest w rozgrywce, nie-bankruci
        std::vector<Player> players;
        Player* currentPlayer;
        std::vector<Player> orderOfMoves;
        Menu* menu;

    public:
        GameController(Board* board, Renderer* renderer, DiceRoller* diceRoller, int numberOfPlayers, Menu* menu);
        ~GameController();
        void init();
        void start();
        void setPlayersOnStart();
        void nextPlayer();
        bool doesSomeoneWin();
        void performAction();
        void takeLoan(Player* player);
        void payLoan(Player* player);
        void simpleDiceRoll();
        void normalDiceRoll();
        void getOutFromJailDiceRoll();
        void payAndGetOutFromJail();
        void setPlayersMoveOrder();
        void propertiesAcquisition(Player* bankrupt, Player* newOwner);
        void bankruptPlayer(Player* player);
        void bankruptPlayerWithoutAcquisition(Player* player);
		void pickBlueCard(Player* player);
		void pickRedCard(Player* player);
        void checkCountryObtain(Player* player, PurchasableField* obtainedField);
};

#endif