#include "gamecontroller.hpp"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

// struktura odpowiada za procedure porownania par <Player, int> w celu posortowania wektora z kolejnoscia graczy
struct moveOrder {
    inline bool operator() (const pair<Player, int>& firstPair, const pair<Player, int>& secondPair) {
        return (firstPair.second > secondPair.second);
    }
};

GameController::GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers) {
    this->board = board;
    this->diceRoller = diceRoller;
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfActivePlayers = numberOfPlayers;

    string names[] = {"Kamil", "Wojciech", "Adrian", "Pawel"};

    for(int i = 0; i < this->numberOfPlayers; i++) {
        bool isComputer = i == 0 ? false : true; // przy 1 obiegu petli i == 0 zatem 1 utworzony gracz to gracz, reszta to komputery

        Player* player = new Player(names[i], isComputer, new PlayerState(1500, false, false), 0);

        this->players.push_back(*player);
    }

    this->currentPlayer = &this->players[0];
}

GameController::~GameController() {
    this->renderMessage("Usuwam obiekt GameController");
    this->players.clear();
    this->orderOfMoves.clear();

    delete this->board;
    delete this->diceRoller;    
}

void GameController::start() {
    this->setPlayersMoveOrder();    
	this->renderPlayersMoveOrder();

    bool isPlaying = true;

    while(isPlaying && this->numberOfActivePlayers > 1) {
        
        if (this->currentPlayer->isComputer()) {
            cout << "KOMPUTER WYKONUJE RUCH" << endl;
        }


        if (this->currentPlayer->isInJail()) {
            
        }
       
        this->renderCurrentPlayer();

       // wybranie akcji gracza
       while(isPlaying && this->numberOfActivePlayers > 1) {
            char playerChoseChar = '0';
            int playerChose = 0;
		
            cout << "Podaj 2 aby usunac gracza, podaj 1 aby przesunac gracza lub 0 aby zakonczyc rozgrywke:" << endl;
		    cin >> playerChoseChar;

		    if (!isdigit(playerChoseChar)) {
			    cout << "Nie podano cyfry!" << endl;
			    continue;			
		    }

		    playerChose = (int) playerChoseChar;
		    playerChose = playerChose - 48;

		    if (playerChose == 0) {
			    isPlaying = false;
			    break;
		    }
		    else if (playerChose == 1) {
                this->renderMessage("To gramy dalej");
                this->nextPlayer();
                break;
            }
            else if (playerChose == 2) {
                this->currentPlayer->setBankrupt(true);
                this->numberOfActivePlayers--;
                
                for(int index = 0; index < this->orderOfMoves.size(); index++) {
                    if (this->currentPlayer == &this->orderOfMoves[index]) {
                        this->nextPlayer();
                        this->orderOfMoves.erase(this->orderOfMoves.begin() + index);
                        break;
                    }
                }
                this->renderPlayersMoveOrder();
            }
            else {
                this->renderMessage("Nie podano poprawnej cyfry!");
                continue;
            }
	    }
    }
}

void GameController::setPlayersOnStart() {

}

void GameController::nextPlayer() {
    if (this->currentPlayer == &this->orderOfMoves[this->numberOfActivePlayers - 1]) {
        this->renderMessage("Ostatni gracz!" + this->currentPlayer->getName());
        this->currentPlayer = &this->orderOfMoves[0];
    }
    else {
        this->currentPlayer++;
    }
}

bool GameController::doesSomeoneWin() {
    return false;
}

void GameController::performAction() {

}

// kazdy z graczy rzuca kostkami, na podstawie wynikow ustalana jest kolejnosc wykonywania ruchow
// na koncu nastepuje ustawienie wskaznika na pierwszego gracza ktory bedzie wykonywal ruch
void GameController::setPlayersMoveOrder() {
    vector<pair<Player, int>> playerRolls;

    this->currentPlayer = &this->players[0];

    for(int i = 0; i < this->players.size(); i++) {
        DiceThrowResult* dtr = this->diceRoller->rollDices();
        int rolledNumber = dtr->firstDice + dtr->secondDice;
        pair<Player, int> currentRoll (*this->currentPlayer, rolledNumber);
        playerRolls.push_back(currentRoll);
        this->currentPlayer++;
    }

    sort(playerRolls.begin(), playerRolls.end(), moveOrder());

    for(vector<pair<Player, int>>::iterator it = playerRolls.begin();
        it != playerRolls.end(); 
        ++it) {
            this->orderOfMoves.push_back(it->first);
    }

    this->currentPlayer = &this->orderOfMoves[0];
}

void GameController::renderPlayersMoveOrder() {
    cout << "Gracze wykonuja ruch w kolejnosci: " << endl;
   
    for(vector<Player>::iterator it = this->orderOfMoves.begin(); it != this->orderOfMoves.end(); ++it) {
        cout << it->getName() << endl;
    }

    cout << endl;
}

// wypisuje na konsole aktualna pozycje kazdego z graczy
void GameController::renderPlayersPositions() {
    for(vector<Player>::iterator it = this->players.begin(); it != this->players.end(); ++it) {
        cout << "Gracz " << it->getName() 
             << " jest na polu " << it->getPosition() 
             << endl;
    }
    
    cout << endl;
}

void GameController::renderCurrentPlayer() {
    cout << "Ruch gracza: " << this->currentPlayer->getName() << endl;
    cout << endl;
}

void GameController::renderMessage(string message) {
    cout << message << endl;
}

