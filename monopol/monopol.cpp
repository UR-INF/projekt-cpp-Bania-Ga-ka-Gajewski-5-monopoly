// monopol.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <string>
#include <time.h>       /* time */
#include "player.hpp"
#include "diceroller.hpp"
#include "menu.hpp"
#include "gamecontroller.hpp"
#include "input.hpp"

using namespace std;

int main()
{
	int numOfPlayersChar = '0';
	int numOfPlayers = 0;

	while(true) {		
		cout << "Podaj ilosc graczy ktora bedzie grac: " << endl;

		numOfPlayers = Input::getDigitKey();

		if ((numOfPlayers > 1) && (numOfPlayers < 5)) {
			cout << "OK! W grze wezmie udzial " << numOfPlayers << " graczy" << endl;
			break;
		}
		else {
			cout << "Liczba musi być z przedzialu 2-4" << endl;
		}
	}

	Board* board = new Board();
	DiceRoller* diceRoller = new DiceRoller();
	Menu* menu = new Menu();

	GameController* gameController = new GameController(board, diceRoller, numOfPlayers, menu);

	gameController->start();

	delete gameController;

	cin >> numOfPlayersChar;
	getchar();
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
