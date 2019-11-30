#include "field.hpp"

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
    private:
        Field* fields[40];
    
    public:
        Board();
        ~Board();
        Field* getField(int index);
        void render(); // metoda do wypisania planszy na konsoli
		void setField(int index, Field* field); // metoda inicjuj�ca obiekt field w tablicy
		bool testFields(); // zetoda swraca true je�li numery pola odpowiadaj� indexom
};

#endif