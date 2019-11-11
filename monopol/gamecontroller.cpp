#include "gamecontroller.hpp"
#include "input.hpp"
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

GameController::GameController(Board* board, DiceRoller* diceRoller, int numberOfPlayers, Menu* menu) {
    this->board = board;
    this->diceRoller = diceRoller;
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfActivePlayers = numberOfPlayers;
    this->menu = menu;

    string names[] = {"Kamil", "Wojciech", "Adrian", "Pawel"};

    for(int i = 0; i < this->numberOfPlayers; i++) {
        bool isComputer = i == 0 ? false : true; // przy 1 obiegu petli i == 0 zatem 1 utworzony gracz to gracz, reszta to komputery

        Player* player = new Player(names[i], isComputer, new PlayerState(1500, false, false), 0);

        this->players.push_back(*player);
    }

    // this->currentPlayer = &this->players[0];
}

GameController::~GameController() {
    this->renderMessage("Usuwam obiekt GameController");
    this->players.clear();
    this->orderOfMoves.clear();

    delete this->board;
    delete this->diceRoller;    
    delete this->menu;
}

void GameController::start() {
    this->setPlayersMoveOrder();    
	this->renderPlayersMoveOrder();
    this->setPlayersOnStart();

    bool isPlaying = true;

    while(isPlaying && this->numberOfActivePlayers > 1) {
        
        this->renderCurrentPlayer();

        if (this->currentPlayer->isComputer()) {
            cout << "KOMPUTER WYKONUJE RUCH" << endl;
        }

        this->menu->render(this->currentPlayer); // wyświetlenie menu
        int playerChose = Input::getDigitKey();

        if (this->currentPlayer->isInJail()) {
            if (playerChose == 9) {
                isPlaying = false;
                break;
            }
            else if (playerChose == 0) {
                // GRACZ WYBRAL RZUT KOSTKAMI
                this->renderMessage("RZUCAM KOSTKAMI W WIEZIENIU");
            }
            else if (playerChose == 1) {
                // GRACZ WYBRAL UZYCIE KARTY
                this->renderMessage("UZYWAM KARTY");
            }
            else if (playerChose == 2) {
                // GRACZ WYBRAL ZAPLATE I RZUT KOSTKAMI
                this->renderMessage("PLACE I RZUCAM");
            }
            else {
                this->renderMessage("Niepoprawny symbol");
                continue;
            }
        }
        else {       
            if (playerChose == 9) {
                isPlaying = false;
                break;
            }
            else if (playerChose == 0) {
                // GRACZ WYBRAL RZUT KOSTKAMI
                this->renderMessage("RZUCAM KOSTKAMI");
                this->simpleDiceRoll();
                this->nextPlayer();
            }
            else if (playerChose == 1) {
                // GRACZ WYBRAL ZAKUP DOMKOW
                this->renderMessage("KUPUJE DOMKI");
            }
            else if (playerChose == 2) {
                // GRACZ WYBRAL WYMIANE
                this->renderMessage("WYMIENIAM");
            }
            else if (playerChose == 3) {
                // GRACZ WYBRAL WZIECIE POZYCZKI Z BANKU
                this->takeLoan(this->currentPlayer);                
            }
            else {
                this->renderMessage("Niepoprawny symbol");
                continue;
            }
        } 
    }
}

void GameController::setPlayersOnStart() {
    for (int index = 0; index < this->players.size(); index++) {
        this->players[index].setPosition(0);
    }
}

// metoda przesuwa wskaznik na nastepnego gracza ktory bedzie wykonywal ruch
// jezeli wskaznik wskazuje na ostatni element vectora orderOfMoves to przesun go na pierwszy element
void GameController::nextPlayer() {

    if (this->currentPlayer == &this->orderOfMoves[this->numberOfActivePlayers - 1]) {
        this->currentPlayer = &this->orderOfMoves[0];
    }
    else {
        this->currentPlayer++;
    }
}

bool GameController::doesSomeoneWin() {
    // tymczasowe implementacja
    return false;
}

void GameController::performAction() {

}

void GameController::takeLoan(Player* player) {
    this->renderMessage("BIORE POZYCZKE");
    
    if (player->hasActiveLoan()) {
        this->renderMessage("NIE MOZESZ WZIAC POZYCZKI DO POKI NIE SPLACISZ POPRZEDNIEJ");

        if (!player->isSolvent(500, true)) {
            this->renderMessage("NIE STAC CIE NA SPLATE POZYCZKI");
            return;            
        }

        this->renderMessage("MOZESZ SPLACIC POZYCZKE \n 1 - SPLAC \n 2 - ANULUJ");
        int playerChose = Input::getDigitKey();

        if(playerChose == 1) {
            player->payBackLoan();
            this->renderMessage("POZYCZKA SPŁACONA");
        }
    }
    else {
        player->takeLoan();
        this->renderMessage("WZIETO POZYCZKE");
    }
}

// Prosty rzut kostkami - rzut -> przesunięcie gracza
void GameController::simpleDiceRoll() {
    DiceThrowResult* dtr = this->diceRoller->rollDices();
    int rolledNumber = dtr->firstDice + dtr->secondDice;
    this->currentPlayer->moveBy(rolledNumber);
    this->renderPlayersPositions();
}

void GameController::bankruptPlayer(Player* player) {
    player->setBankrupt(true);
    this->numberOfActivePlayers--;
                    
    for(int index = 0; index < this->orderOfMoves.size(); index++) {
        if (player == &this->orderOfMoves[index]) {
            this->nextPlayer();
            this->orderOfMoves.erase(this->orderOfMoves.begin() + index);
            break;
        }
    }
}

// kazdy z graczy rzuca kostkami, na podstawie wynikow ustalana jest kolejnosc wykonywania ruchow
// na koncu nastepuje ustawienie wskaznika na pierwszego gracza ktory bedzie wykonywal ruch
// PRZEZ TO ZE SA PRZEKAZYWANE WARTOSCI TO vector orderOfMoves przechowuje inne obiekty niz vetor players
// DO POPRAWY
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
    this->renderMessage("Gracze wykonuja ruch w kolejnosci: ");
   
    for(vector<Player>::iterator it = this->orderOfMoves.begin(); it != this->orderOfMoves.end(); ++it) {
        this->renderMessage(it->getName());
    }

    cout << endl;
}

// wypisuje na konsole aktualna pozycje kazdego z graczy
void GameController::renderPlayersPositions() {
    for(vector<Player>::iterator it = this->orderOfMoves.begin(); it != this->orderOfMoves.end(); ++it) {
        cout << "Gracz " << it->getName() 
             << " jest na polu " << it->getPosition() 
             << endl;
    }
    
    cout << endl;
}

void GameController::renderCurrentPlayer() {
    this->renderMessage("Ruch gracza: " + this->currentPlayer->getName());
    cout << endl;
}

void GameController::renderMessage(string message) {
    cout << message << endl;
}

