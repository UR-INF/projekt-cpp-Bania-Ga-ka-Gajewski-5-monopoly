#include "gamecontroller.hpp"
#include <string>
#include <iostream>

GameController::GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers) {
    this->board = board;
    this->diceRoller = diceRoller;
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfActivePlayers = numberOfPlayers;

    std::string names[] = {"Kamil", "Wojciech", "Adrian", "Pawel"};

    for(int i = 0; i < this->numberOfPlayers; i++) {
        Player* player = new Player(names[i], new PlayerState(1500, false), 0);

        this->players.push_back(*player);
    }

    this->currentPlayer = &players[0];
}

GameController::~GameController() {

}

void GameController::start() {

}

void GameController::setPlayersOnStart() {

}

void GameController::nextPlayer() {

}

bool GameController::doesSomeoneWin() {
    return false;
}

void GameController::performAction() {

}

void GameController::setPlayersMoveOrder() {
    std::map<int, Player*> playersOrderOfMoves;

    for(int i = 0; i < this->players.size(); i++) {
        DiceThrowResult* dtr = this->diceRoller->rollDices();
        int rolledNumber = dtr->firstDice + dtr->secondDice;
        playersOrderOfMoves[rolledNumber] = this->currentPlayer;
        this->currentPlayer++;
    }
    
    this->orderOfMoves = playersOrderOfMoves;
    this->currentPlayer = this->orderOfMoves.begin()->second;
}

void GameController::renderPlayersMoveOrder() {
    std::cout << "Gracze wykonuja ruch w kolejnosci: " << endl;
    for(std::map<int, Player*>::iterator it = this->orderOfMoves.begin();
        it != this->orderOfMoves.end(); 
        ++it) {
            std::cout << it->second->getName() << endl;
    }
}

// wypisuje na konsole aktualna pozycje kazdego z graczy
void GameController::renderPlayersPositions() {
    for(std::vector<Player>::iterator it = this->players.begin();
        it != this->players.end(); 
        ++it) {
            std::cout << "Gracz " << it->getName() 
                      << " jest na polu " << it->getPosition() 
                      << endl;
    }
}

void GameController::renderCurrentPlayer() {
    std::cout << "Ruch gracza: " << this->currentPlayer->getName() << endl;
}
