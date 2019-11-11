#include "playerstate.hpp"
#include <string>

#ifndef Player_h
#define Player_h

using namespace std;

class Player {
    private:
        string name;
        bool computer;
        PlayerState* playerState;
        int position;
        bool activeLoan;
        int cashGain; // ilosc pieniedzy otrzymywana za przejscie przez pole START
    
    public:
        Player(string name, bool isComputer, PlayerState *playerState, int position);
        ~Player();

        string getName();
        bool isComputer();
        void setName(string name);
        int getPosition();
        void setPosition(int position);
        bool isInJail();
        bool isSolvent(int rent);
        bool isSolvent(int rent, bool onlyCash);
        bool isBankrupt();
        void setBankrupt(bool isBankrupt);
        bool hasActiveLoan();
        void takeLoan();
        void payBackLoan();

};

#endif