#include "gamecontroller.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "propertyfield.hpp"
#include "railwayfield.hpp"
#include "rentmultipierfield.hpp"
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
    this->rentMultipier = 1;

    string names[] = {"Kamil", "Wojciech", "Adrian", "Pawel"};

    for(int i = 0; i < this->numberOfPlayers; i++) {
        bool isComputer = i == 0 ? false : true; // przy 1 obiegu petli i == 0 zatem 1 utworzony gracz to gracz, reszta to komputery

        Player* player = new Player(names[i], isComputer, new PlayerState(1500, false, false, 0), 0);

        this->players.push_back(*player);
    }

    // this->currentPlayer = &this->players[0];
}

GameController::~GameController() {
    // this->renderer->renderMessage("Usuwam obiekt GameController");
    this->players.clear();
    this->orderOfMoves.clear();

    delete this->board;
    delete this->diceRoller;  
    delete this->menu;
    delete this->renderer;
}

void GameController::start() {
    this->setPlayersMoveOrder();    
	this->renderer->renderPlayersMoveOrder(this->orderOfMoves);
    this->setPlayersOnStart();
    /*
        static_cast<PropertyField*>(this->board->getField(1))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(3))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(6))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(8))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(9))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(12))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(16))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(18))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(19))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(35))->setOwner(this->currentPlayer);
        static_cast<PropertyField*>(this->board->getField(37))->setOwner(&this->orderOfMoves[2]);
        static_cast<PropertyField*>(this->board->getField(39))->setOwner(&this->orderOfMoves[2]);

        this->currentPlayer->addProperty(1);
        this->currentPlayer->addProperty(3);
        this->currentPlayer->addProperty(6);
        this->currentPlayer->addProperty(8);
        this->currentPlayer->addProperty(9);
        this->currentPlayer->addProperty(12);
        this->currentPlayer->addProperty(16);
        this->currentPlayer->addProperty(18);
        this->currentPlayer->addProperty(19);
        this->currentPlayer->addProperty(35);

        this->currentPlayer->addCountry(this->board->getCountry("Grecja"));
        this->currentPlayer->addCountry(this->board->getCountry("Wlochy"));
        this->currentPlayer->addCountry(this->board->getCountry("Wielka Brytania"));
        
        this->currentPlayer += 2;
        this->currentPlayer->addProperty(37);
        this->currentPlayer->addProperty(39);
        this->currentPlayer->addCountry(this->board->getCountry("Austria"));
        
        Player* own = this->currentPlayer;

        this->currentPlayer = &this->orderOfMoves[0];
        
        
        this->renderer->renderBoard(this->board);

        this->renderer->renderMessage("Bede przepisywal posiadlosci: ");
        this->propertiesAcquisition(this->currentPlayer, own);
        this->bankruptPlayer(this->currentPlayer);
        this->nextPlayer();

        this->renderer->renderBoard(this->board);

        this->renderer->renderMessage("Bede przepisywal posiadlosci: ");
        this->propertiesAcquisition(this->currentPlayer, own);
        this->bankruptPlayer(this->currentPlayer);
        this->nextPlayer();
    */

    // this->renderer->renderBoard(this->board);

    bool isPlaying = true;
	int iterationCount = 0;

    while (!doesSomeoneWin()) {
        this->renderer->renderMessage("Multipier: " + to_string(this->rentMultipier));

        iterationCount++;

        if (iterationCount % 100 == 0) {
            this->rentMultipier++;
        }    

        this->renderer->renderPlayersInfo(this->orderOfMoves, this->board);

        this->renderer->renderCurrentPlayer(this->currentPlayer);

        if (this->currentPlayer->isComputer()) {
            cout << "KOMPUTER WYKONUJE RUCH" << endl;
            this->computerMove();
            continue;            
        }

        this->menu->construct(this->currentPlayer); // utworzenie menu dla konkretnego gracza
        this->renderer->renderMenu(this->menu); // wyswietlenie menu

        int playerChose;

        while(true) {
            playerChose = Input::getDigitKey();

            if (this->menu->getCurrentMenu().size() - 1 < playerChose) {
                this->renderer->renderMessage("Podano niepoprawna opcje");
                continue;
            }

            break;
        }

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
                /*
                    czy gracz posiada jakies panstwo:
                        wyswietl pola z posiadanych panstw
                        wybierz pole ktore chcesz ulepszyc
                        czy pola maja ten sam poziom:
                            czy gracza stac na kupno domku:
                                property_upgrade
                */
                if (this->currentPlayer->hasAnyCountry()) {
                    this->renderer->renderMessage("Posiadane kraje: ");
                    for (auto country : this->currentPlayer->getOwnedCountries()) {
                        this->renderer->renderMessage(country->getName() + ":");

                        for(auto fieldIndex : country->getProperties()) {
                            PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(fieldIndex));        
                            this->renderer->renderMessage(propertyField->toString()+" - Koszt rozbudowy: "+to_string(propertyField->getUpgradeCost()));
                        }
                    }  
                    
                    // wybor pola do zakupu domku 
                    this->renderer->renderMessage("Podaj nr nieruchomosci ktora chcesz ulepszyc, podaj 0 aby anulowac");
                    int playerChose = 0;
                    bool isCorrectChose = true;

                    while (true) {                        
                        // playerChose = Input::getDigitKey();
                        playerChose = Input::getNumber();

                        for (auto country : this->currentPlayer->getOwnedCountries()) {
                            set<int> properties = country->getProperties(); 
                            isCorrectChose = properties.find(playerChose) != properties.end() || playerChose == 0;                       
                            
                            if (isCorrectChose) {
                                break;
                            }
                        } 

                        if (isCorrectChose) {
                            break;
                        }                    
                    }

                    // jesli wybral 0 - anuluj zakup
                    if (playerChose == 0) {
                        this->renderer->renderMessage("Anulowano zakup");
                        continue;
                    }

                    PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(playerChose));

                    if (propertyField->getHousingLevel() == 5) {
                        this->renderer->renderMessage("To pole zostalo ulepszone na maxa");
                        break;
                    }

                    int upgradeCost = propertyField->getUpgradeCost();

                    if (this->currentPlayer->isSolvent(upgradeCost, true)) {
                        this->currentPlayer->payMoney(upgradeCost);
                        propertyField->upgrade();
                    }
                    else {
                        this->renderer->renderMessage("Nie stac cie na zakup domku na tym polu");
                        break;
                    }

                }   
                else {
                    this->renderer->renderMessage("Nie posiadasz zadnego panstwa");
                    continue;
                }            
                
                continue;
            case SELL_HOUSE:
                if (this->currentPlayer->hasAnyCountry()) {
                    this->renderer->renderMessage("Posiadane kraje: ");
                    for (auto country : this->currentPlayer->getOwnedCountries()) {
                        this->renderer->renderMessage(country->getName() + ":");

                        for(auto fieldIndex : country->getProperties()) {
                            PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(fieldIndex));        
                            this->renderer->renderMessage(propertyField->toString());
                        }
                    }

                    // wybor pola z ktorego domek ma byc sprzedany
                    this->renderer->renderMessage("Podaj nr nieruchomosci z ktorej chcesz sprzedac domek, 0 jesli chcesz anulowac:");
                    int playerChose = 0;
                    bool isCorrectChose = true;

                    while (true) {                        
                        // playerChose = Input::getDigitKey();
                        playerChose = Input::getNumber();

                        for (auto country : this->currentPlayer->getOwnedCountries()) {
                            set<int> properties = country->getProperties(); 
                            isCorrectChose = properties.find(playerChose) != properties.end() || playerChose == 0;                       
                            
                            if (isCorrectChose) {
                                break;
                            }
                        } 

                        if (isCorrectChose) {
                            break;
                        }                    
                    }

                    // jesli wybral 0 - anuluj sprzedaz
                    if (playerChose == 0) {
                        this->renderer->renderMessage("Anulowano zakup");
                        continue;
                    }

                    PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(playerChose));

                    if (propertyField->getHousingLevel() == 0) {
                        this->renderer->renderMessage("Na tym polu nie ma nic co mozna sprzedac");
                        break;
                    }

                    int upgradeCost = propertyField->getUpgradeCost();

                    propertyField->degrade();
                    this->currentPlayer->earnMoney(upgradeCost / 2);

                    this->renderer->renderMessage("Domek na polu " + propertyField->getPropertyInfo() + " zostal sprzedany");
                }
                continue;
            case OUT_OF_JAIL_ROLL_DICE:
                this->getOutFromJailDiceRoll();
                this->nextPlayer();
                break;
            case USE_CARD_TO_GET_FREE:
                this->currentPlayer->useOutOfJailCard();
                this->currentPlayer->getOutOfJail();
                this->simpleDiceRoll();
                this->nextPlayer();
                break;
            case PAY_AND_GET_FREE:
                this->payAndGetOutFromJail();
                this->nextPlayer();
                break;
            case SHOW_BOARD:
                this->renderer->renderBoard(this->board);
                continue;
            default:
                this->renderer->renderMessage("Niepoprawny symbol");
                continue;
        }

    }
    
    for (auto player : this->orderOfMoves) {
        if (!player.isBankrupt()) {
            this->renderer->renderMessage("");
            this->renderer->renderMessage("Gracz " + player.getName() + " wygral te rozgrywke!");
            this->renderer->renderMessage("");
            this->renderer->renderMessage("Koncowy stan graczy: ");
            this->renderer->renderPlayersInfo(this->orderOfMoves, this->board);
            this->renderer->renderMessage("");
            this->renderer->renderMessage("Koncowy stan planszy: ");
            this->renderer->renderBoard(this->board);
            this->renderer->renderMessage("Dziekujemy za rozegrana partie");
            break;
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

    do {
        if (this->currentPlayer == &this->orderOfMoves[this->orderOfMoves.size() - 1]) {
            this->currentPlayer = &this->orderOfMoves[0];
        }
        else {
            this->currentPlayer++;
        }
    } while(this->currentPlayer->isBankrupt());
}

bool GameController::doesSomeoneWin() {
    if (this->numberOfActivePlayers > 1) {
        return false;
    }

    return true;
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
            this->renderer->renderMessage("Stajesz na pole: Podatek od Luksusu");
            if(this->currentPlayer->isSolvent(100, true)) {
                this->renderer->renderMessage("Placisz 100$");
                this->currentPlayer->payMoney(100);
            }
            else if (!this->currentPlayer->hasActiveLoan()) {
                this->renderer->renderMessage("Nie stac cie na zaplate podatku od luksusu. Bierzesz pozyczke i placisz 100");
                this->currentPlayer->takeLoan();
                this->renderer->renderMessage("Placisz 100$");
                this->currentPlayer->payMoney(100);
            }
            else {
                this->renderer->renderMessage("Nie jestes w stanie zaplacic podatku od luksusu - bankrutujesz");
                this->bankruptPlayerWithoutAcquisition(this->currentPlayer);
            }
            break;
        case INCOME_TAX:
            this->renderer->renderMessage("Stajesz na pole: Podatek dochodowy");
            if(this->currentPlayer->isSolvent(200, true)) {
                this->renderer->renderMessage("Musisz zaplacic podatek dochodowy - placisz 200");
                this->currentPlayer->payMoney(200);
            }
            else if (!this->currentPlayer->hasActiveLoan()) {
                this->renderer->renderMessage("Nie stac cie na zaplate podatku dochodowego. Bierzesz pozyczke i placisz 200");
                this->currentPlayer->takeLoan();
                this->renderer->renderMessage("Placisz 200$");
                this->currentPlayer->payMoney(200);
            }
            else
            {
                this->renderer->renderMessage("Nie jestes w stanie zaplacic podatku dochodowego - bankrutujesz");
                this->bankruptPlayerWithoutAcquisition(this->currentPlayer);
            }
            break;
        case RED_CHANCE:
            pickRedCard(this->currentPlayer);
            break;
        case BLUE_CHANCE:
            pickBlueCard(this->currentPlayer);
            break;
        /* 
                czy nieruchomosc nie ma wlasciciela:
                    czy gracza stac na zakup:
                        czy gracz chce kupic:  
                            kup
                            break
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
        case RAILWAY:
        case ELECTRICITY:
        case WATER_SUPPLY_NETWORK:
        {
            PurchasableField* purchasableField = static_cast<PurchasableField*>(contextField);
            this->renderer->renderMessage("Stajesz na polu: " + purchasableField->toString());

            Player* propertyOwner = purchasableField->getOwner();       

            if (!propertyOwner) {
                if (this->currentPlayer->isSolvent(purchasableField->getPrice(), true)) {
                    // JESLI JEST RUCH KOMPUTERA
                    if (this->currentPlayer->isComputer()) {
                        this->renderer->renderMessage("Komputer-Gracz " + this->currentPlayer->getName() + " kupuje pole nr: " + to_string(purchasableField->getFieldNumber()));
                        this->currentPlayer->payMoney(purchasableField->getPrice());
                        this->currentPlayer->addProperty(indexOfFieldContext);
                        purchasableField->setOwner(this->currentPlayer);       
                                
                        if (typeid(*contextField) == typeid(PropertyField)) {
                            this->checkCountryObtain(this->currentPlayer, purchasableField);
                        }

                        return;
                    }

                    this->menu->constructConfirm();                    
                    this->renderer->renderMessage("Cena: " + to_string(purchasableField->getPrice()));
                    this->renderer->renderMessage("Czy chcesz kupic te nieruchomosc?");
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
                                this->currentPlayer->payMoney(purchasableField->getPrice());
                                this->currentPlayer->addProperty(indexOfFieldContext);
                                purchasableField->setOwner(this->currentPlayer);       
                                
                                if (typeid(*contextField) == typeid(PropertyField)) {
                                    this->checkCountryObtain(this->currentPlayer, purchasableField);
                                }

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
            }
            else {
                if (this->currentPlayer == propertyOwner) {
                    this->renderer->renderMessage("Odwiedzasz swoja nieruchomosc");
                    break;
                }
                else {
                    this->renderer->renderMessage("Placisz czynsz graczowi: " + propertyOwner->getName());

                    int rentToPay = 0;

                    if (typeid(purchasableField) == typeid(RailwayField)) {
                        rentToPay = static_cast<RailwayField*>(purchasableField)->getRent(propertyOwner->getProperties()) * this->rentMultipier;
                    }
                    else if (typeid(purchasableField) == typeid(RentMultipierField)) {
                        rentToPay = purchasableField->getRent() * this->diceRoller->getRolledNumber() * this->rentMultipier;
                    }
                    else {
                        rentToPay = purchasableField->getRent() * this->rentMultipier;
                    }

                    if(this->currentPlayer->isSolvent(rentToPay, true)) {
                        this->renderer->renderMessage("Placisz " + to_string(rentToPay));
                        this->currentPlayer->payMoney(rentToPay);
                        propertyOwner->earnMoney(rentToPay);
                        break;
                    }
                    else if (!this->currentPlayer->hasActiveLoan() && this->currentPlayer->isSolvent(500 + rentToPay, true)) {
                        this->renderer->renderMessage("Aby splacic czynsz bierzesz pozyczke");
                        this->currentPlayer->takeLoan();
                        this->currentPlayer->payMoney(rentToPay);
                        propertyOwner->earnMoney(rentToPay);
                        break;
                    }
                    else {
                        this->renderer->renderMessage("Nie jestes w stanie zaplacic czynszu w wysokosci: " + to_string(rentToPay));
                        this->renderer->renderMessage("Bankrutujesz! Twoje nieruchomosci przejmuje: " + propertyOwner->getName());
                        this->propertiesAcquisition(this->currentPlayer, propertyOwner);
                        this->bankruptPlayer(this->currentPlayer);
                        break;
                    }
                }
            }
            break;
        }           
    }
}

void GameController::takeLoan(Player* player) {
    player->takeLoan();
    this->renderer->renderMessage("WZIETO POZYCZKE");
    // this->renderer->renderMessage("BIORE POZYCZKE");
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
    this->performAction();
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

            // jesli w wyniku tego debla gracz zbankrutowal lub trafil do wiezienia to metoda sie konczy, nastepne rzuty nie sa wykonywane
            if (this->currentPlayer->isBankrupt() || this->currentPlayer->isInJail()) {
                return;
            }
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
            this->performAction();
            return;
        }
    }
}

void GameController::payAndGetOutFromJail() {
    this->currentPlayer->payMoney(50);
    this->currentPlayer->getOutOfJail();
    this->simpleDiceRoll();
}

void GameController::bankruptPlayer(Player* player) {
    player->setBankrupt(true);
    this->numberOfActivePlayers--;
}

void GameController::bankruptPlayerWithoutAcquisition(Player* player) {
    set<int> properties = player->getProperties();

    for(auto propertyIndex : properties) {
        // cout << "Indeks usuwanej nieruchomosci: " << propertyIndex << endl;
        PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(propertyIndex));
        // cout << "Ustawiam wlasciciela posiadlosci: " << propertyField->getFieldNumber() << " na NULL" << endl;
        propertyField->setOwner(NULL);
        // cout << "Owner: " << propertyField->getOwner() << endl;
    }

    player->clearProperties();
    this->bankruptPlayer(player);
}

void GameController::propertiesAcquisition(Player* bankrupt, Player* newOwner) {
    set<int> properties = bankrupt->getProperties();
    vector<PurchasableField*> obtainedFields = vector<PurchasableField*>();

    for(auto propertyIndex : properties) {
        PurchasableField* purchasableField = static_cast<PurchasableField*>(this->board->getField(propertyIndex));
        purchasableField->setOwner(newOwner);
        newOwner->addProperty(propertyIndex);
        // this->renderer->renderMessage("Nowy wlasciciel pola " + purchasableField->toString() + " - " + purchasableField->getOwner()->getName());
        obtainedFields.push_back(purchasableField);
    }

    for(auto obtainedField : obtainedFields) {
        if (typeid(*obtainedField) == typeid(PropertyField)) {            
            this->checkCountryObtain(newOwner, obtainedField);
        }
        else {
            // this->renderer->renderMessage("Pole inne niz PropertyField, nie sprawdzam zatem");
        }
    }

    int bankruptMoney = bankrupt->getPlayerState().getMoney();
    bankrupt->payMoney(bankruptMoney);
    newOwner->earnMoney(bankruptMoney);

    bankrupt->clearProperties();
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
    this->renderer->renderMessage("Pole: " + to_string(player->getPosition()) + " - Niebieska Szansa " + card.getDescription());
	switch (card.getCardId())
	{
	case 0:
		//Wychodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.
		player->addOutOfJailCard();
		break;
	case 1:
		//Wracasz do \"WIEDNIA\"
		player->setPosition(39);
        performAction();
        //Field* contextField = this->board->getField(39);
        //PurchasableField* purchasableField = static_cast<PurchasableField*>(contextField);
        //Player* propertyOwner = purchasableField->getOwner;
		break;
	case 2:
		//Płacisz za karę 20$ lub ciągniesz \"SZANSĘ\" z drugiego zestawu (czerwonego)
		//jeśli niezdolny zapłacić automatycznie ciągnie karte
		if (player->isComputer()) {
            if (player->isSolvent(20, true)) {
                player->payMoney(20);
            }
            else {
                pickRedCard(player);
            }
            break;
        }

        if (player->isSolvent(20)) {
            this->renderer->renderMessage("0 By zaplacic kare");
            this->renderer->renderMessage("1 By pobrac karte z zestawu czerwonego");
            int playerChose = Input::getDigitKey();
            switch (playerChose)
            {
            case 0:
                player->payMoney(20);
            case 1:
                pickRedCard(player);
            default:
                break;
            }
		}
		else {
            this->renderer->renderMessage("Nie masz pieniedzy by zaplacic kare. Bierzesz karte z czerwonego zestawu.");
            pickRedCard(player);
            //break or return?
			}
		break;
	case 3:
		//Wracasz na \"START\"
		player->setPosition(0);
		break;
	case 4:
		//Idziesz do więzienia.Nie przechodzisz przez \"START\". Nie otrzymujesz 200$.
        player->goToJail();
		break;
	case 5:
		//Płacisz koszty leczenia w wysokości 20$.
        if (player->isSolvent(20)) {
            player->payMoney(20);
        }
        else {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Masz aktywna pozyczke. Nie mozesz wziasc kolejnej co prowadzi do bankructwa.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else
            {
                this->renderer->renderMessage("Musisz wziac pozyczke by zaplacic kare");
                takeLoan(player);
                player->payMoney(20);
            }
        }
		break;
	case 6:
		//Bank omylił się na Twoją krozyść. Otrzymujesz 400$.
		player->earnMoney(400);
		break;
	case 7:
		//Zająłeś II miejsce w konkursie piękności - otrzymujesz z banku 200$.
        player->earnMoney(200);
		break;
	case 8:
		//Otrzymujesz roczną rentę w wysokości 200$.
        player->earnMoney(200);
		break;
	case 9:
		//Bank wypłaci ci należne 7% od kapitałów - otrzymujesz 50$.
		player->earnMoney(50);
		break;
	case 10:
        //Placisz skladke ubezpieczeniowa w wysokosci 20$.
        if (player->isSolvent(20)) {
            player->payMoney(20);
        }
        else {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Masz aktywna pozyczke. Nie mozesz wziasc kolejnej co prowadzi do bankructwa.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else
            {
                this->renderer->renderMessage("Musisz wziac pozyczke by zaplacic kare");
                takeLoan(player);
                player->payMoney(20);
            }
        }
		break;
	case 11:
        //Z magazynu, w ktorym kupujesz otrzymujesz rabat w wyoskosci 20$.
        player->earnMoney(20);
		break;
	case 12:
        //Placisz na budowe szpitala 400$.
        if (player->isSolvent(400)) {
            player->payMoney(400);
        }
        else {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Masz aktywna pozyczke. Nie mozesz wziasc kolejnej co prowadzi do bankructwa.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else
            {
                this->renderer->renderMessage("Musisz wziac pozyczke by zaplacic kare");
                takeLoan(player);
                player->payMoney(400);
            }
        }
		break;
	case 13:
		//Otrzymujesz w spadku 200$.
		player->earnMoney(200);
		break;
	case 14:
        //Masz urodziny - otrzymujesz od kazdego gracza po 20$.
        for (Player otherplayer : orderOfMoves) {
            if (otherplayer.getName() != player->getName()&& !otherplayer.isBankrupt()) {
                if (otherplayer.isSolvent(20)) {
                    otherplayer.payMoney(20);
                    player->earnMoney(20);
                }
                else
                {
                    if (otherplayer.hasActiveLoan()) {
                        this->renderer->renderMessage(otherplayer.getName()+" ma aktywna pozyczke nie moze wziac kolejnej wiec bankrutuje.");
                        bankruptPlayerWithoutAcquisition(&otherplayer);
                    }
                    else {
                        this->renderer->renderMessage(otherplayer.getName() + " musial wziac pozyczke by kupic prezent.");
                        takeLoan(&otherplayer);
                        player->earnMoney(20);
                    }
                }
                
            }
        }
		break;
	default:
		break;
	}
}

void GameController::pickRedCard(Player* player) {
	//wylosowanie kartty czerwonej
	Card card = board->pickRedCard();
    this->renderer->renderMessage("Pole: "+to_string(player->getPosition())+" - Czerwona Szansa: " + card.getDescription());



    switch (card.getCardId())
    {
    case 0:
        //Wracasz na \"START\"
        player->setPosition(0);
        break;
    case 1:
        //Piles w czasie pracy, placisz kare 40$.
        if (player->isSolvent(40)) {
            player->payMoney(40);
        }
        else {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Masz aktywna pozyczke. Nie mozesz wziasc kolejnej co prowadzi do bankructwa.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else
            {
                this->renderer->renderMessage("Musisz wziac pozyczke by zaplacic kare");
                takeLoan(player);
                player->payMoney(40);
            }
        }
        break;
    case 2:
        //Idziesz do wiezienia. Nie przechodzisz przez \"START\". Nie otrzymujesz premii 200$.
        player->setPosition(10);
        break;
    case 3:
        //Remontujesz swoje domy. Placisz do banku za kazdy dom 50$, za kazdy hotel 200$.
        {
        int renovatePrice = renovationCost(player);
        this->renderer->renderMessage("Calkowity koszt remontu wynosi: " + to_string(renovatePrice));
        if (player->isSolvent(renovatePrice)) {
            this->renderer->renderMessage("Zaplaciles za remont: " + to_string(renovatePrice));
            player->payMoney(renovatePrice);
        }
        else
        {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Nie mozesz wziac kolejnego kredytu. Bakrutujesz.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else {
                player->takeLoan();
                if (player->isSolvent(renovatePrice)) {
                    this->renderer->renderMessage("Zaplaciles za remont: " + to_string(renovatePrice));
                    player->payMoney(renovatePrice);
                }
                else
                {
                    this->renderer->renderMessage("Koszty remontu przerastaja twoja zdolnosc kredytowa. Bakrutujesz.");
                    bankruptPlayerWithoutAcquisition(player);
                }
            }
        }
    }
		break;
	case 4:
		//Cofasz się o 3 pola.
		player->setPosition(player->getPosition() - 3);
        performAction();
		break;
	case 5:
		//Wcyhodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.
		player->addOutOfJailCard();
		break;
	case 6:
        //Idziesz do \"NEAPOLU\". Jezeli przechodzisz przez \"START\" otrzymasz 200$. Neapol(6)
        player->moveBy(distanceTo(player->getPosition(),6));
        performAction();
		break;
	case 7:
        //Wracasz do \"Madrytu\"
        player->setPosition(14);
        performAction();
		break;
	case 8:
        //Zobowiazany jestes zmodernizowac swoje miasto, placisz do banku za kazdy dom 80$, za kazdy hotel 230$.
        {
        int renovatePrice = renovationCost(player);
        this->renderer->renderMessage("Calkowity koszt remontu wynosi: " + to_string(renovatePrice));
        if (player->isSolvent(renovatePrice)) {
            this->renderer->renderMessage("Zaplaciles za remont: " + to_string(renovatePrice));
            player->payMoney(renovatePrice);
        }
        else
        {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Nie mozesz wziac kolejnego kredytu. Bakrutujesz.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else {
                player->takeLoan();
                if (player->isSolvent(renovatePrice)) {
                    this->renderer->renderMessage("Zaplaciles za remont: " + to_string(renovatePrice));
                    player->payMoney(renovatePrice);
                }
                else
                {
                    this->renderer->renderMessage("Koszty remontu przerastaja twoja zdolnosc kredytowa. Bakrutujesz.");
                    bankruptPlayerWithoutAcquisition(player);
                }
            }
        }
        break;
        }
	case 9:
        //Idziesz do \"KOLEI WSCHODNICH\". Jezeli przechodzisz przez \"START\" otrzymasz 200$. Koleje wschodnie(35)
        player->moveBy(distanceTo(player->getPosition(), 35));
        performAction();
		break;
	case 10:
        //Wracasz do \"Brukseli\". Jezeli przechodzisz przez \"START\" otrzymujesz 200$. Bruksela(23)
        player->moveBy(distanceTo(player->getPosition(), 23));
        performAction();
		break;
	case 11:
		//Bank wpłaca Ci należne odsetkiw  wysokości 300$.
		player->earnMoney(300);
		break;
	case 12:
        //Mandat za szybka jazde. Placisz 30$.
        if (player->isSolvent(30)) {
            player->payMoney(30);
        }
        else {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Masz aktywna pozyczke. Nie mozesz wziasc kolejnej co prowadzi do bankructwa.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else
            {
                this->renderer->renderMessage("Musisz wziac pozyczke by zaplacic kare");
                takeLoan(player);
                player->payMoney(30);
            }
        }
		break;
	case 13:
        //Placisz oplate za szkole 300$.
        if (player->isSolvent(300)) {
            player->payMoney(300);
        }
        else {
            if (player->hasActiveLoan()) {
                this->renderer->renderMessage("Masz aktywna pozyczke. Nie mozesz wziasc kolejnej co prowadzi do bankructwa.");
                bankruptPlayerWithoutAcquisition(player);
            }
            else
            {
                this->renderer->renderMessage("Musisz wziac pozyczke by zaplacic kare");
                takeLoan(player);
                player->payMoney(300);
            }
        }
		break;
	case 14:
		//Bank wypłaca Ci pprocent w wysokości 100$.
		player->earnMoney(100);
		break;
	case 15:
		//Rozwiązałeś dobrze krzyżówkę. Jako I nagrodę otrzymujesz 200$.
		player->earnMoney(200);
		break;
	default:
		break;
	}
}


int GameController::distanceTo(int curentPos, int destination) {
    if (curentPos < destination) {
        return destination - curentPos;
    }
    else
    {
        return 40 - curentPos + destination;
    }
}

int GameController::renovationCost(Player* player) {
    int renovatePrice = 0;
    //this->renderer->renderMessage("! Obliczam renovation cost");
    
    for (int i : player->getProperties()) {
        //this->renderer->renderMessage("! Wszedłem do petli");
        Field* field = board->getField(i);
        if (field->getFieldType() == PROPERTY) {
            //this->renderer->renderMessage("! sprawdzam czy pole jest propert");
            PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(i));
                int fieldLv = propertyField->getHousingLevel();
                if (fieldLv == 5) {
                    //this->renderer->renderMessage("! zwiekszam koszt o hotel");
                    renovatePrice += 230;
                }
                else {
                    //this->renderer->renderMessage("! zwiekszam koszt o dom");
                    renovatePrice += fieldLv * 80;
                }
        }
    }
    //this->renderer->renderMessage("! koszt renowacji: "+renovatePrice);
    return renovatePrice;
}

// metoda sprawdza czy po uzyskaniu nieruchomosci gracz posiadl cale panstwo
void GameController::checkCountryObtain(Player* owner, PurchasableField* obtainedField) {
    PropertyField* obtainedProperty = static_cast<PropertyField*>(obtainedField);

    string countryName = obtainedProperty->getCountryName();

    Country* countryToCheck = this->board->getCountry(countryName);
    
    bool hadObtainedCountry = true;

    // this->renderer->renderMessage("Sprawdzam czy gracz " + owner->getName() + " posiada pozostale miasta z panstwa " + countryName);
    for(auto fieldIndex : countryToCheck->getProperties()) {
        PurchasableField* purchasableField = static_cast<PurchasableField*>(this->board->getField(fieldIndex));        
        // this->renderer->renderMessage(purchasableField->toString());

        if (purchasableField->getOwner() != owner) {
            hadObtainedCountry = false;
            break;
        }
    }

    if (hadObtainedCountry) {
        owner->addCountry(countryToCheck);
    }
}

// metoda wykonuje ruch komputera
void GameController::computerMove() {    
/* ALGORYTM KOMPUTERA                
    if jest w wiezieniu:
        if posiada karte na wyjscie z wiezienia:
            uzyj karty
            break
        else if jest wyplacalny 200:
            zaplac i rzuc kostka
            break
        else:
            rzut na wyjscie z wiezienia
            break
    else:
        if posiada zaciagnieta pozyczke:
            if moze splacic pozyczke:
                if is solvent 700:
                    splac pozyczke
        else if jesli ma mniej niz 150:
            wez pozyczke

        if posiada jakies panstwo:
            if moze kupic jakas nieruchomosc zeby mu zostalo wiecej niz 200:
                kup domek
            else if ma mniej niz 100:
                sprzedaj domek
                    
        rzut kostka
        -obsluga karty
        -kupno nieruchomosci:
*/
    if (this->currentPlayer->isInJail()) {
        if (this->currentPlayer->hasOutOfJailCard()) {
            this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " uzywa karty na wyjscie z wiezienia");
            this->currentPlayer->useOutOfJailCard();
            this->currentPlayer->getOutOfJail();
            this->simpleDiceRoll();
            return;           
        }
        else if (this->currentPlayer->isSolvent(200, true)) {
            this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " placi 50$, rzuca kostkami i wychodzi z wiezienia");
            this->payAndGetOutFromJail();
            return;
        }
        else {
            this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " wykonuje rzut na wyjscie z wiezienia");
            this->getOutFromJailDiceRoll();
            return;
        }
    }
    else {
        if (this->currentPlayer->hasActiveLoan()) {
            if (this->currentPlayer->getCanPayLoan()) {
                if (this->currentPlayer->isSolvent(700, true)) {
                    this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " splaca pozyczke");
                    this->currentPlayer->payBackLoan();
                }
            }
        } 
        else if (this->currentPlayer->getPlayerState().getMoney() < 150) {
            this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " bierze pozyczke");
            this->currentPlayer->takeLoan();
        }

        if (this->currentPlayer->hasAnyCountry()) {
            set<Country*> computerCountries = this->currentPlayer->getOwnedCountries();           

            if (this->currentPlayer->getPlayerState().getMoney() < 100) {
                bool isSearchingForHouseToSell = true;

                for (auto country : computerCountries) {
                    set<int> computerCountryProperties = country->getProperties();

                    for (auto computerPropertyIndex : computerCountryProperties) {
                        PropertyField* computerPropertyField = static_cast<PropertyField*>(this->board->getField(computerPropertyIndex));

                        if (computerPropertyField->getHousingLevel() == 0) {
                            continue;
                        }

                        int moneyToAdd = computerPropertyField->getUpgradeCost() / 2;
                        computerPropertyField->degrade();
                        this->currentPlayer->earnMoney(moneyToAdd);

                        this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " sprzedal domek na polu " + computerPropertyField->getPropertyInfo());
                        
                        if (this->currentPlayer->getPlayerState().getMoney() > 100) {
                            isSearchingForHouseToSell = false;
                        }
                    }

                    if (!isSearchingForHouseToSell) {
                        break;
                    } 
                }
            }
            else {
                for (auto country : computerCountries) {
                    set<int> computerCountryProperties = country->getProperties();

                    for (auto computerPropertyIndex : computerCountryProperties) {                        
                        PropertyField* computerPropertyField = static_cast<PropertyField*>(this->board->getField(computerPropertyIndex));
                            
                        if (computerPropertyField->getHousingLevel() == 5) {
                            continue;
                        }

                        int upgradeCost = computerPropertyField->getUpgradeCost();

                        if (this->currentPlayer->isSolvent(upgradeCost + 200, true)) {
                            this->renderer->renderMessage("Komputer-Gracz: " + this->currentPlayer->getName() + " ulepsza pole " + computerPropertyField->getPropertyInfo());
                            this->currentPlayer->payMoney(upgradeCost);
                            computerPropertyField->upgrade();
                        }
                        else {
                            break;
                        }                    
                    }
                }
            }           
        }

        this->normalDiceRoll();
        this->nextPlayer();
    }
}