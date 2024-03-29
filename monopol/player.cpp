#include "player.hpp"
#include <iostream>

using namespace std;

Player::Player(string name, bool isComputer, PlayerState *playerState, int position) {
	this->setName(name);
	this->computer = isComputer;
	this->playerState = playerState;
	this->setPosition(position);
	this->activeLoan = false;
	this->canPayLoan = true;
	this->cashGain = 200;
	this->playerProperties = set<int>();
	this->ownedCountries = set<Country*>();
};

Player::~Player() {
	// cout << "Usuwam obiekt Player" << endl;
	// delete this->playerState;
	playerProperties.clear();
	ownedCountries.clear();
};

string Player::getName() {
	if (this->isComputer()) {
		return this->name + " - AI";
	}
	
	return this->name;
};

bool Player::isComputer() {
	return this->computer;
}

void Player::setName(string name) {
	this->name = name;
};

int Player::getPosition() {
	return this->position;
};

void Player::setPosition(int position) {
	this->position = position;
};

void Player::moveBy(int distance) {
	if (this->position + distance > 39) {
		this->setPosition((this->position + distance) % 40);
		
		// cout << "Przechodze przez pole START" << endl;

		this->earMoneyFromStart();

		// cout << "Zarabiam " << this->cashGain << endl;

		this->canPayLoan = true;		
	}
	else {
		int currentPosition = this->getPosition();
		this->setPosition(currentPosition + distance);
	}
}

bool Player::isInJail() {
	return this->playerState->getIsInJail();
}

bool Player::isSolvent(int rent) {
	// narazie jest sprawdzany tylko warunek posiadanych pieniedzy
	// do tego trzeba dodac czy wartosc majątku > rent
	if (this->playerState->getMoney() > rent) {
		return true;
	}
	else {
		return false;
	}

}

bool Player::isSolvent(int rent, bool onlyCash) {
	if (onlyCash) {
		if (this->playerState->getMoney() > rent) {
			return true;
		}

		return false;
	}

	return this->isSolvent(rent);
}

bool Player::isBankrupt() {
	return this->playerState->isBankrupt();
}

void Player::setBankrupt(bool isBankrupt) {
	this->playerState->setBankrupt(isBankrupt);
}

// czy gracz ma pozyczke do splaty
bool Player::hasActiveLoan() {
	return this->activeLoan;
}

bool Player::getCanPayLoan() {
	return this->canPayLoan;
}

// wziecie pozyczki
void Player::takeLoan() {
	this->earnMoney(500);
	this->activeLoan = true;
	this->cashGain = 100;
	// uniemozliwiam splate pozyczki do momentu przejscia przez start
	this->canPayLoan = false;
}

// splata pozyczki
void Player::payBackLoan() {
	this->payMoney(500);
	this->activeLoan = false;
	this->cashGain = 200;
}

void Player::goToJail() {
	this->playerState->setIsInJail(true);
	this->setPosition(10); // 10 to nr pola z wiezieniem
}

void Player::getOutOfJail() {
	this->playerState->setIsInJail(false);
}

void Player::addOutOfJailCard() {
	int numOfCards = playerState->getOutOfJailCards();
	numOfCards++;
	playerState->setOutOfJailCards(numOfCards);
}

bool Player::hasOutOfJailCard() {
	if (playerState->getOutOfJailCards() > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Player::useOutOfJailCard() {
	int numOfCards = playerState->getOutOfJailCards();
	numOfCards--;
	if (numOfCards < 0) {
		// throw "Probojesz uzyć karty ktorej nie masz !";
		return;
	}
	playerState->setOutOfJailCards(numOfCards);
	this->getOutOfJail();
}

void Player::addProperty(int fieldId) {
	this->playerProperties.insert(fieldId);
}

void Player::removeProperty(int fieldId) {
	this->playerProperties.erase(this->playerProperties.find(fieldId));
}

void Player::clearProperties() {
	this->playerProperties.clear();
	this->ownedCountries.clear();
}

set<int> Player::getProperties() {
	return this->playerProperties;
}

bool Player::hasAnyCountry() {
	return (this->ownedCountries.size() > 0);
}

set<Country*> Player::getOwnedCountries() {
	return this->ownedCountries;
}

void Player::addCountry(Country* country) {
	this->ownedCountries.insert(country);
}

PlayerState Player::getPlayerState() {
	return *this->playerState;
}

void Player::earnMoney(int money) {
	this->playerState->addMoney(money);
}

void Player::payMoney(int cost) {
	this->playerState->removeMoney(cost);
}

void Player::earMoneyFromStart() {
	this->playerState->addMoney(this->cashGain);
}