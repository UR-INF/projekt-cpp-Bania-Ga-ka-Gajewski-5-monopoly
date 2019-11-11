#include "player.hpp"

using namespace std;

Player::Player(string name, bool isComputer, PlayerState *playerState, int position) {
	this->setName(name);
	this->computer = isComputer;
	this->playerState = playerState;
	this->setPosition(position);
	this->activeLoan = false;
};

Player::~Player() {};

string Player::getName() {
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

// wziecie pozyczki
void Player::takeLoan() {
	int currentMoney = this->playerState->getMoney();
	currentMoney += 500;
	this->playerState->setMoney(currentMoney);
	this->activeLoan = true;
}

// splata pozyczki
void Player::payBackLoan() {
	int currentMoney = this->playerState->getMoney();
	currentMoney -= 500;
	this->playerState->setMoney(currentMoney);
	this->activeLoan = false;
}