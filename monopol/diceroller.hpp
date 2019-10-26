#include "dicethrowresult.hpp"

#ifndef DICEROLLER_H
#define DICEROLLER_H

class DiceRoller {
    private:
        DiceThrowResult* throwResult;

    public:
        DiceRoller();
        ~DiceRoller();
        DiceThrowResult* rollDices();
        bool isDouble();        
};

#endif