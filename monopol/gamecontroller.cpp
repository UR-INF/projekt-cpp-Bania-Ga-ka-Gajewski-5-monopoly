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
	//pickBlueCard(currentPlayer);
    while(isPlaying && this->numberOfActivePlayers > 1) {
        
        this->renderer->renderCurrentPlayer(this->currentPlayer);

        if (this->currentPlayer->isComputer()) {
            cout << "KOMPUTER WYKONUJE RUCH" << endl;
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
                this->payAndGetOutFromJail();
                this->nextPlayer();
                break;
            default:
                this->renderer->renderMessage("Niepoprawny symbol");
                continue;
        }

        this->renderer->renderMessage("Aktualne pozycje na planszy: ");
        this->renderer->renderPlayerPositions(this->orderOfMoves);

        this->renderer->renderMessage("Aktualny stan planszy");
        this->renderer->renderBoard(this->board);
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
                this->renderer->renderMessage("Nie jestes w stanie zaplacic podatku od luksusu - bankrutujesz");
                this->bankruptPlayerWithoutAcquisition(this->currentPlayer);
            }
            break;
        case INCOME_TAX:
            if(this->currentPlayer->isSolvent(200, true)) {
                this->currentPlayer->payMoney(200);
            }
            else
            {
                this->renderer->renderMessage("Nie jestes w stanie zaplacic podatku dochodowego - bankrutujesz");
                this->bankruptPlayerWithoutAcquisition(this->currentPlayer);
            }
            break;
        case RED_CHANCE:
            pickBlueCard(this->currentPlayer);
            break;
        case BLUE_CHANCE:
            pickRedCard(this->currentPlayer);
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
                        rentToPay = static_cast<RailwayField*>(purchasableField)->getRent(propertyOwner->getProperties());
                    }
                    else if (typeid(purchasableField) == typeid(RentMultipierField)) {
                        rentToPay = purchasableField->getRent() * this->diceRoller->getRolledNumber();
                    }
                    else {
                        rentToPay = purchasableField->getRent();
                    }

                    if(this->currentPlayer->isSolvent(rentToPay, true)) {
                        this->renderer->renderMessage("Placisz " + to_string(rentToPay));
                        this->currentPlayer->payMoney(rentToPay);
                        propertyOwner->earnMoney(rentToPay);
                        break;
                    }
                    else {
                        this->renderer->renderMessage("Brankrutujesz! Twoje nieruchomosci przejmuje: " + propertyOwner->getName());
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
    // player->getPlayerState().setOutOfJailCards(0);    
    /*            
    for(int index = 0; index < this->orderOfMoves.size(); index++) {
        if (player == &this->orderOfMoves[index]) {
            this->nextPlayer();
            this->orderOfMoves.erase(this->orderOfMoves.begin() + index);
            break;
        }
    }
    */
}

void GameController::bankruptPlayerWithoutAcquisition(Player* player) {
    set<int> properties = player->getProperties();

    for(auto propertyIndex : properties) {
        cout << "Indeks usuwanej nieruchomosci: " << propertyIndex << endl;
        PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(propertyIndex));
        cout << "Ustawiam wlasciciela posiadlosci: " << propertyField->getFieldNumber() << " na NULL" << endl;
        propertyField->setOwner(NULL);
        cout << "Owner: " << propertyField->getOwner() << endl;
    }

    player->clearProperties();
    this->bankruptPlayer(player);
}

void GameController::propertiesAcquisition(Player* bankrupt, Player* newOwner) {
    set<int> properties = bankrupt->getProperties();

    for(auto propertyIndex : properties) {
        PropertyField* propertyField = static_cast<PropertyField*>(this->board->getField(propertyIndex));
        propertyField->setOwner(newOwner);
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
        performAction();
        //Field* contextField = this->board->getField(39);
        //PurchasableField* purchasableField = static_cast<PurchasableField*>(contextField);
        //Player* propertyOwner = purchasableField->getOwner;
		break;
	case 2:
		//Płacisz za karę 20$ lub ciągniesz \"SZANSĘ\" z drugiego zestawu (czerwonego)
		//jeśli niezdolny zapłacić automatycznie ciągnie karte
		if (player->isSolvent(20)) {
            this->renderer->renderMessage("0 By zaplacic kare");
            this->renderer->renderMessage("1 By pobrać partę z zestawu czerwonego");
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
		player->setPosition(10);
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
            if (otherplayer.getName() != player->getName()) {
                if (otherplayer.isSolvent(20)) {
                    otherplayer.payMoney(20);
                    player->earnMoney(20);
                }
                else
                {
                    if (otherplayer.hasActiveLoan()) {
                        this->renderer->renderMessage(otherplayer.getName()+" ma aktywna pozyczke nie moze wziac kolejnej wiec bankrutuje.");
                        //bankruptPlayerWithoutAcquisition(otherplayer);
                    }
                    else {
                        this->renderer->renderMessage(otherplayer.getName() + " musial wziac pozyczke by kupic prezent.");
                        //takeLoan(otherplayer);
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
    this->renderer->renderMessage("RED CARD: " + card.getDescription());



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
        this->renderer->renderMessage("Calkowity koszt remontu wynosi: " + renovatePrice);
        if (player->isSolvent(renovatePrice)) {
            this->renderer->renderMessage("Zaplaciles za remont: " + renovatePrice);
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
                    this->renderer->renderMessage("Zaplaciles za remont: " + renovatePrice);
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
		break;
	case 5:
		//Wcyhodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.
		player->addOutOfJailCard();
		break;
	case 6:
        //Idziesz do \"NEAPOLU\". Jezeli przechodzisz przez \"START\" otrzymasz 200$. Neapol(6)
        player->setPosition(distanceTo(player->getPosition(),6));
		break;
	case 7:
        //Wracasz do \"Madrytu\"
        player->setPosition(14);
		break;
	case 8:
        //Zobowiazany jestes zmodernizowac swoje miasto, placisz do banku za kazdy dom 80$, za kazdy hotel 230$.
        {
        int renovatePrice = renovationCost(player);
        this->renderer->renderMessage("Calkowity koszt remontu wynosi: " + renovatePrice);
        if (player->isSolvent(renovatePrice)) {
            this->renderer->renderMessage("Zaplaciles za remont: " + renovatePrice);
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
                    this->renderer->renderMessage("Zaplaciles za remont: " + renovatePrice);
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
		break;
	case 10:
        //Wracasz do \"Brukseli\". Jezeli przechodzisz przez \"START\" otrzymujesz 200$. Bruksela(23)
        player->moveBy(distanceTo(player->getPosition(), 23));
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