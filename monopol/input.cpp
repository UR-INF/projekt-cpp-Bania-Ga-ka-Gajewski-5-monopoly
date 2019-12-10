#include "input.hpp"
#include <iostream>
#include <string>

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

int Input::getNumber() {
    bool isGoodInput = true;
    string playerChose = "";

    while (true) {
        isGoodInput = true;

        cin >> playerChose;

        for (char const &c : playerChose) {
            if (!isdigit(c)) {
                cout << "Nie podano liczby" << endl;
                isGoodInput = false;
            }
        }

        if (isGoodInput) {
            int result = stoi(playerChose);
            // cout << result << " - " << typeid(result).name() << endl;

            return result;
        }
    }
}