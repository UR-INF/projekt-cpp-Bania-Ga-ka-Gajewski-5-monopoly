#include "board.hpp"
#include "field.hpp"
#include <iostream>

Board::Board() {
    // tutaj będą tworzone wszystkie elementy typu field, tj miasta, koleje itd.

}

Board::~Board() {
    std::cout << "Usuwam obiekt Board" << endl;
}

Field* Board::getField(int index) {
    return this->fields[index];
}

void Board::render() {
    std::cout << "Renderuje plansze" << endl;
}