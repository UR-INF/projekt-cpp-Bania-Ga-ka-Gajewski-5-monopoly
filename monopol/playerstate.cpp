#include "playerstate.hpp"
#include <iostream>

PlayerState::PlayerState(int money, bool isInJail, bool bankrupt, int outOfJailCards) {
    this->setMoney(money);
    this->setIsInJail(isInJail);
    this->setBankrupt(bankrupt);
	this->setOutOfJailCards(outOfJailCards);
};

PlayerState::~PlayerState() {
    //std::cout << "Usuwam obiekt PlayerState" << std::endl;
};

bool PlayerState::getIsInJail() {
    return this->isInJail;
};

int PlayerState::getMoney() {
    return this->money;
};

void PlayerState::setMoney(int money) {
    this->money = money;
};

void PlayerState::setIsInJail(bool isInJail) {
    this->isInJail = isInJail;
};

bool PlayerState::isBankrupt() {
    return this->bankrupt;
}

void PlayerState::setBankrupt(bool bankrupt) {
    this->bankrupt = bankrupt;
}

int PlayerState::getOutOfJailCards() {
	return this->outOfJailCards;
}

void PlayerState::setOutOfJailCards(int outOfJailCards) {
	this->outOfJailCards = outOfJailCards;
}

void PlayerState::addMoney(int money) {
    int currentMoney = this->getMoney();
    this->setMoney(currentMoney + money);
}

void PlayerState::removeMoney(int money) {
    int currentMoney = this->getMoney();
    this->setMoney(currentMoney - money);
}
