#include "gamecontroller.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "propertyfield.hpp"
#include "field.hpp"
#include "board.hpp"
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

GameController::GameController(Board* board, Renderer* renderer, DiceRoller* diceRoller, int numberOfPlayers, Menu* menu) {
    this->board = board;
    this->renderer = renderer;
    this->diceRoller = diceRoller;
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfActivePlayers = numberOfPlayers;
    this->menu = menu;

    string names[] = {"Kamil", "Wojciech", "Adrian", "Pawel"};

    for(int i = 0; i < this->numberOfPlayers; i++) {
        bool isComputer = i == 0 ? false : true; // przy 1 obiegu petli i == 0 zatem 1 utworzony gracz to gracz, reszta to komputery

        Player* player = new Player(names[i], isComputer, new PlayerState(1500, false, false, 0), 0);

        this->players.push_back(*player);
    }

    // this->currentPlayer = &this->players[0];
}

GameController::~GameController() {
    this->renderer->renderMessage("Usuwam obiekt GameController");
    this->players.clear();
    this->orderOfMoves.clear();

    delete this->board;
    delete this->diceRoller;  
    delete this->currentPlayer;  
    delete this->menu;
}

void GameController::start() {
    this->setPlayersMoveOrder();    
	this->renderer->renderPlayersMoveOrder(this->orderOfMoves);
    this->setPlayersOnStart();
    this->renderer->renderBoard(this->board);

    bool isPlaying = true;
	// pickBlueCard(currentPlayer);
    while(isPlaying && this->numberOfActivePlayers > 1) {
        
        this->renderer->renderCurrentPlayer(this->currentPlayer);

        if (this->currentPlayer->isComputer()) {
            cout << "KOMPUTER WYKONUJE RUCH" << endl;
        }

        this->menu->construct(this->currentPlayer); // utworzenie menu dla konkretnego gracza
        this->renderer->renderMenu(this->menu); // wyswietlenie menu

        int playerChose = Input::getDigitKey();

        switch(this->menu->getCurrentMenu()[playerChose]->getAction()) {
            case NORMAL_DICE_ROLL:
                this->normalDiceRoll();
                this->nextPlayer();
                break;
            case TAKE_LOAN:
                this->takeLoan(this->currentPlayer);
                continue;
            case PAY_LOAN:
                this->payLoan(this->currentPlayer);
                continue;
            case BUY_HOUSE:
                continue;
            case SELL_HOUSE:
                continue;
            case EXCHANGE:
                continue;
            case OUT_OF_JAIL_ROLL_DICE:
                this->getOutFromJailDiceRoll();
                this->nextPlayer();
                break;
            case USE_CARD_TO_GET_FREE:
                continue;
            case PAY_AND_GET_FREE:

                continue;
            default:
                this->renderer->renderMessage("Niepoprawny symbol");
                continue;
        }

        this->renderer->renderMessage("Aktualne pozycje na planszy: ");
        this->renderer->renderPlayerPositions(this->orderOfMoves);

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
    int indexOfFieldContext = this->currentPlayer->getPosition();

    Field* contextField = this->board->getField(indexOfFieldContext);

    switch(contextField->getFieldType()) {
        case START:
            // this->currentPlayer->earMoneyFromStart();
            // Obsluga tego pola jest juz zaimplementowana w Player MoveBy
            break;
        case JAIL:
            this->renderer->renderMessage("Odwiedzasz wiezienie");
            break;
        case GO_TO_JAIL:
            this->renderer->renderMessage("Idziesz do wiezienia!");
            this->currentPlayer->goToJail();
            break;
        case FREE_PARKING:
            this->renderer->renderMessage("Odpoczywasz na darmowym parkingu");
            break;
        case LUXURY_TAX:
            if(this->currentPlayer->isSolvent(100, true)) {
                this->currentPlayer->payMoney(100);
            }
            else {
                this->bankruptPlayer(this->currentPlayer);
            }
            break;
        case INCOME_TAX:
            if(this->currentPlayer->isSolvent(200, true)) {
                this->currentPlayer->payMoney(200);
            }
            else
            {
                this->bankruptPlayer(this->currentPlayer);
            }
            break;
        /* 
                czy nieruchomosc nie ma wlasciciela:
                    czy gracza stac na zakup:
                        czy gracz chce kupic:  
                            kup
                        else
                            licytacja
                    else
                        licytacja
                else
                    czy to nieruchomosc aktualnego gracza
                        break
                    else
                        kalkulacja zaplaty
                        czy gracza stac na splate czynszu
                            gracz placi
                            break
                        else
                            bankructwo
                            break
                        
            */    
        case PROPERTY:
            PropertyField* propertyField = static_cast<PropertyField*>(contextField);
            this->renderer->renderMessage("Stajesz na polu: " + propertyField->getPropertyInfo());
            Player* propertyOwner = propertyField->getOwner();

            if (!propertyOwner) {
                if (this->currentPlayer->isSolvent(propertyField->getPrice(), true)) {
                    this->menu->constructConfirm();
                    this->renderer->renderMenu(this->menu);
                    
                    int playerChose = 0;

                    while(true) {
                        playerChose = Input::getDigitKey();

                        if (this->menu->getCurrentMenu().size() - 1 < playerChose) {
                            this->renderer->renderMessage("Podano niepoprawna opcje");
                            continue;
                        }

                        switch(this->menu->getCurrentMenu()[playerChose]->getAction()) {
                            case CONFIRM:
                                this->currentPlayer->payMoney(propertyField->getPrice());
                                this->currentPlayer->addProperty(indexOfFieldContext);
                                propertyField->setOwner(this->currentPlayer);                                  
                                this->renderer->renderMessage("Nieruchomosc zakupiona");                              
                                return;
                            case CANCEL:
                                this->renderer->renderMessage("Zrezygnowano z zakupu nieruchomosci");
                                return;
                            default:
                                break;
                        }
                    }                                       
                }
                else {
                    /*
                        LICYTACJA
                    */
                }
            }
            else {
                if (this->currentPlayer == propertyOwner) {
                    this->renderer->renderMessage("Odwiedzasz swoja nieruchomosc");
                    break;
                }
                else {
                    this->renderer->renderMessage("Płacisz czynsz graczowi: " + propertyOwner->getName());

                    int rentToPay = propertyField->getCurrentRent();

                    if(this->currentPlayer->isSolvent(rentToPay, true)) {
                        this->currentPlayer->payMoney(rentToPay);
                        propertyOwner->earnMoney(rentToPay);
                        break;
                    }
                    else {
                        this->bankruptPlayer(this->currentPlayer);
                        break;
                    }
                }
            }

            break;            
    }
}

void GameController::takeLoan(Player* player) {
    player->takeLoan();
    this->renderer->renderMessage("WZIETO POZYCZKE");
    this->renderer->renderMessage("BIORE POZYCZKE");
}

void GameController::payLoan(Player* player) {
    player->payBackLoan();
    this->renderer->renderMessage("POZYCZKA SPLACONA");
}
// Prosty rzut kostkami - rzut -> przesunięcie gracza
void GameController::simpleDiceRoll() {
    DiceThrowResult* dtr = this->diceRoller->rollDices();
    int rolledNumber = dtr->firstDice + dtr->secondDice;
    this->currentPlayer->moveBy(rolledNumber);
    this->renderer->renderPlayerPositions(this->orderOfMoves);
}

void GameController::normalDiceRoll() {
    int doubles = 0;
    int rolledNumber = 0;
    DiceThrowResult* dtr = NULL;

    while(true) {
        dtr = this->diceRoller->rollDices();
        rolledNumber = dtr->firstDice + dtr->secondDice;

        if (dtr->isDouble()) {
            this->renderer->renderMessage("WYRZUCONO DEBEL");
            doubles++;

            if (doubles == 3) {
                this->renderer->renderMessage("IDZIESZ DO WIEZIENIA");
                this->currentPlayer->goToJail();
                return;
            }

            this->currentPlayer->moveBy(rolledNumber);

            // WYKONAJ AKCJE DLA POLA
            this->performAction();
        }
        else {
            this->currentPlayer->moveBy(rolledNumber);
            // WYKONAJ AKCJE DLA POLA
            this->performAction();
            return; 
        }
    }
}

void GameController::getOutFromJailDiceRoll() {
    DiceThrowResult* dtr = NULL;

    for(int roll = 0; roll < 3; roll++) {
        dtr = this->diceRoller->rollDices();

        if (dtr->isDouble()) {
            int rolledNumber = dtr->firstDice + dtr->secondDice;
            this->currentPlayer->getOutOfJail();
            this->currentPlayer->moveBy(rolledNumber);

            return;
        }
    }
}

void GameController::bankruptPlayer(Player* player) {
    player->setBankrupt(true);
    player->clearProperties();
    // player->getPlayerState().setOutOfJailCards(0);
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

void GameController::pickBlueCard(Player* player) {
	//wylosowanie karty niebieskiej
	Card card = board->pickBlueCard();
    this->renderer->renderMessage("BLUE CARD: " + card.getDescription());
	switch (card.getCardId())
	{
	case 0:
		//Wychodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.
		player->addOutOfJailCard();
		break;
	case 1:
		//Wracasz do \"WIEDNIA\"
		player->setPosition(39);
		break;
	case 2:
		//Płacisz za karę 20$ lub ciągniesz \"SZANSĘ\" z drugiego zestawu (czerwonego)
		//jeśli niezdolny zapłacić automatycznie ciągnie karte
		if (player->getPlayerState().getMoney() < 20) {
			pickRedCard(player);
			//break or return?
		}
		else {
			this->renderer->renderMessage("0 By zapłacić karę");
			this->renderer->renderMessage("1 By pobrać partę z zestawu czerwonego");
			int playerChose = Input::getDigitKey();
			switch (playerChose)
			{
			case 0:
				player->getPlayerState().setMoney(player->getPlayerState().getMoney()-20);
			case 1:
				pickRedCard(player);
			default:
				break;
			}
		}
		break;
	case 3:
		//Wracasz na \"START\"
		player->setPosition(0);
		break;
	case 4:
		//Idziesz do więzienia.Nie przechodzisz przez \"START\". Nie otrzymujesz 200$.
		player->setPosition(10);
		break;
	case 5:
		//Płacisz koszty leczenia w wysokości 20$.
		break;
	case 6:
		//Bank omylił się na Twoją krozyść. Otrzymujesz 400$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney()+400);
		break;
	case 7:
		//Zająłeś II miejsce w konkursie piękności - otrzymujesz z banku 200$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 200);
		break;
	case 8:
		//Otrzymujesz roczną rentę w wysokości 200$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 200);
		break;
	case 9:
		//Bank wypłaci ci należne 7% od kapitałów - otrzymujesz 50$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 50);
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		//Otrzymujesz w spadku 200$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 200);
		break;
	case 14:
		break;
	default:
		break;
	}
}

void GameController::pickRedCard(Player* player) {
	//wylosowanie kartty czerwonej
	Card card = board->pickRedCard();
    this->renderer->renderMessage("RED CARD: " + card.getDescription());
	switch (card.getCardId())
	{
	case 0:
		break;
	case 1:
		break;
	case 2:		
		break;
	case 3:
		break;
	case 4:
		//Cofasz się o 3 pola.
		player->setPosition(player->getPosition() - 3);
		break;
	case 5:
		//Wcyhodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.
		player->addOutOfJailCard();
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		//Bank wpłaca Ci należne odsetkiw  wysokości 300$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 300);
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		//Bank wypłaca Ci pprocent w wysokości 100$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 100);
		break;
	case 15:
		//Rozwiązałeś dobrze krzyżówkę. Jako I nagrodę otrzymujesz 200$.
		player->getPlayerState().setMoney(player->getPlayerState().getMoney() + 200);
		break;
	default:
		break;
	}
}
