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
		void setField(int index, Field* field); // metoda inicjuj¹ca obiekt field w tablicy
		bool testFields(); // metoda zwraca true jeœli numery pola odpowiadaj¹ indexom
};

#endif