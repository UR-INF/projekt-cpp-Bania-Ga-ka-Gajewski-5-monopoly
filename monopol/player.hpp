#include "playerstate.hpp"
#include "country.hpp"
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
		bool canPayLoan; // mo�na sp�aci� je�eli gracz przeszed� przez pole start ( warto�� zmieniana jest w metodzie moveby)
        int cashGain; // ilosc pieniedzy otrzymywana za przejscie przez pole START
		set<int> playerProperties;
        set<Country*> ownedCountries;
    
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
        void clearProperties();
        set<int> getProperties();
        bool hasAnyCountry();
        set<Country*> getOwnedCountries();
        void addCountry(Country* country);
        void earnMoney(int money);
        void payMoney(int cost);
        void earMoneyFromStart();
		PlayerState getPlayerState();

};

#endif