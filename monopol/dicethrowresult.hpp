#ifndef DICETHROWRESULT_H
#define DICETHROWRESULT_H

struct DiceThrowResult {
    public:
        int firstDice;
        int secondDice;        
        int doublesInRow;
        bool doubles;
        bool isDouble();
};

#endif