#include "playerstate.hpp"
#include <string>
#include <set>

#ifndef Player_h
#define Player_h

using namespace std;

class Player {
    private:
        string name;
        bool computer;
        PlayerState* playerState;
        int position; // pozycja na planszy [0 - 39]
        bool activeLoan;
		bool canPayLoan; // mo¿na sp³aciæ je¿eli gracz przeszed³ przez pole start ( wartoœæ zmieniana jest w metodzie moveby)
        int cashGain; // ilosc pieniedzy otrzymywana za przejscie przez pole START
		set<int> playerProperties;
    
    public:
        Player(string name, bool isComputer, PlayerState *playerState, int position);
        ~Player();

        string getName();
        bool isComputer();
        void setName(string name);
        int getPosition();
        void setPosition(int position);
        void moveBy(int distance);
        bool isInJail();
        bool isSolvent(int rent);
        bool isSolvent(int rent, bool onlyCash);
        bool isBankrupt();
        void setBankrupt(bool isBankrupt);
        bool hasActiveLoan();
        void takeLoan();
        void payBackLoan();
        void goToJail();
        void getOutOfJail();
		void addOutOfJailCard();
		bool hasOutOfJailCard();
		void useOutOfJailCard();
		void addProperty(int fieldId);
		void removeProperty(int fieldId);
		PlayerState getPlayerState();

};

#endif