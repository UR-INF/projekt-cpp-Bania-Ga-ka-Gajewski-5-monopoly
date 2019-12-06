#include "field.hpp"
#include "card.h"

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
    private:
        Field* fields[40];

		Card* redCards[16];
		Card* blueCards[15];
    
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
};

#endif