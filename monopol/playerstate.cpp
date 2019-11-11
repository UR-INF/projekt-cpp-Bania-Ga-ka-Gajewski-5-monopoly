#include "playerstate.hpp"

PlayerState::PlayerState(int money, bool isInJail, bool bankrupt) {
    this->setMoney(money);
    this->setIsInJail(isInJail);
    this->setBankrupt(bankrupt);
};

PlayerState::~PlayerState() {};

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

