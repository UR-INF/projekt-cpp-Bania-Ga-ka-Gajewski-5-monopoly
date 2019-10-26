#include "gamecontroller.hpp"

GameController::GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers) {
    this->board = board;
    this->diceRoller = diceRoller;
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfActivePlayers = numberOfPlayers;
}

GameController::~GameController() {

}

void GameController::start() {

}

void setPlayersOnStart() {

}

void nextPlayer() {

}

bool doesSomeoneWin() {

}

void performAction() {

}

std::map<int, Player*> setPlayersMoveOrder() {
    
}
