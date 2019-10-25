#include "playerstate.hpp"


PlayerState::PlayerState(int money, bool isInJail) {
    this->setMoney(money);
    this->setIsInJail(isInJail);
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