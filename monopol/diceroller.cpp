#include "diceroller.hpp"
#include <time.h>
#include <iostream>

DiceRoller::DiceRoller() {
    std::srand(time(NULL));
    this->throwResult = new DiceThrowResult();
}

DiceRoller::~DiceRoller() {
    std::cout << "Usuwam obiekt DiceRoller" << std::endl;
}

DiceThrowResult* DiceRoller::rollDices() {
    int firstDiceRoll = std::rand() % 6 + 1;
    int secondDiceRoll = std::rand() % 6 + 1;

    this->throwResult->firstDice = firstDiceRoll;
    this->throwResult->secondDice = secondDiceRoll;
    this->throwResult->doubles = (firstDiceRoll == secondDiceRoll);

    if(this->throwResult->isDouble()) {
        this->throwResult->doublesInRow++;
    }
    else {
        this->throwResult->doublesInRow = 0;
    }

    return this->throwResult;
}

bool DiceRoller::isDouble() {
    return throwResult->isDouble();
}

int DiceRoller::getRolledNumber() {
    return (this->throwResult->firstDice + this->throwResult->secondDice);
}