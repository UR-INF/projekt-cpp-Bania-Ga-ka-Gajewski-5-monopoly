#include "field.hpp"
#include "card.h"
#include "deque"

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
    private:
        Field* fields[40];

	    deque<Card> redCards;
        deque<Card> blueCards;
    
    public:
        Board();
        ~Board();
        Field* getField(int index);
        void render(); // metoda do wypisania planszy na konsoli

		void setField(int index, Field* field); // metoda inicjuj�ca obiekt field w tablicy
		bool testFields(); // metoda zwraca true je�li numery pola odpowiadaj� indexom

		Card pickBlueCard();
		Card pickRedCard();
};

#endif