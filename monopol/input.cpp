#include "input.hpp"
#include <iostream>

using namespace std;

int Input::getDigitKey() {
    char playerChoseChar = '0';
    int playerChose = 0;  

    while (true) {
        cin >> playerChoseChar;

        if (!isdigit(playerChoseChar)) {
            cout << "Nie podano cyfry!" << endl;
            cout << "Wprowadz jeszcze raz!" << endl;
            continue;
        }

        break;
    }
    
    playerChose = (int) playerChoseChar;
    playerChose = playerChose - 48;

    return playerChose;
}