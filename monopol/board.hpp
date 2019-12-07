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
		void setField(int index, Field* field); // metoda inicjuj¹ca obiekt field w tablicy
		bool testFields(); // metoda zwraca true jeœli numery pola odpowiadaj¹ indexom
		//void shuffleCards(Card** cards, int count);
		Card pickBlueCard();
		Card pickRedCard();
};

#endif