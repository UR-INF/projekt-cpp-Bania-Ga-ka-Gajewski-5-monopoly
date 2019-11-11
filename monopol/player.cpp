#include "player.hpp"
#include <iostream>

using namespace std;

Player::Player(string name, bool isComputer, PlayerState *playerState, int position) {
	this->setName(name);
	this->computer = isComputer;
	this->playerState = playerState;
	this->setPosition(position);
	this->activeLoan = false;
	this->cashGain = 200;
};

Player::~Player() {
	cout << "Usuwam obiekt Player" << endl;
	delete this->playerState;
};

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

void Player::moveBy(int distance) {
	if (this->position + distance > 39) {
		this->setPosition((this->position + distance) % 40);
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

// wziecie pozyczki
void Player::takeLoan() {
	int currentMoney = this->playerState->getMoney();
	currentMoney += 500;
	this->playerState->setMoney(currentMoney);
	this->activeLoan = true;
	this->cashGain = 100;
}

// splata pozyczki
void Player::payBackLoan() {
	int currentMoney = this->playerState->getMoney();
	currentMoney -= 500;
	this->playerState->setMoney(currentMoney);
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