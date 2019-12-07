#include "field.hpp"
#include "Card.h"
#include "country.hpp"
#include <map>

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
    private:
        Field* fields[40];

		Card* redCards[16];
		Card* blueCards[15];

        // Country* countries[8];
        map<string, Country*> countries;
    
    public:
        Board();
        ~Board();
        Field* getField(int index);
        void render(); // metoda do wypisania planszy na konsoli
		void setField(int index, Field* field); // metoda inicjuj�ca obiekt field w tablicy
		bool testFields(); // metoda zwraca true je�li numery pola odpowiadaj� indexom
		void shuffleCards(Card** cards, int count);
		Card pickBlueCard();
		Card pickRedCard();
        map<string, Country*> getCountries();
        void setCountries(map<string, Country*> countries);
        Country* getCountry(string name);
        void setCountry(string name, Country* country);
};

#endif