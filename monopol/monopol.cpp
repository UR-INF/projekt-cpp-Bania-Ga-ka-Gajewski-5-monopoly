// monopol.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <time.h>       /* time */
int throw_bones() {
	return rand() % 16 + 2;
}

class Player {
	int name;
	int money;
	int current_field;

public:
	int get_name() { return name; }
	void set_name(int name) {
		this->name = name;
	}

	int get_money() { return money; }
	void set_money(int money) {
		this->money = money;
	}

	int get_current_field() { return current_field; }
	void set_current_field(int current_field){
		this->current_field = current_field;
	}
};

class Field {
	int id;
	int country;
	int field_owner;
	int price_of_field;
	int rent_price_tier1;
	int rent_price_tier2;
	int rent_price_tier3;
	int rent_price_tier4;
	int home_count;

public:
	int get_id() { return id; }
	void set_id(int id) {
		this->id = id;
	}

	int get_country() { return country; }
	void set_country(int country) {
		this->country = country;
	}

	int get_field_owner() { return field_owner; }
	void set_field_owner(int field_owner) {
		this->field_owner = field_owner;
	}

	int get_price_of_field() { return price_of_field; }
	void set_price_of_field(int price_of_field) {
		this->price_of_field = price_of_field;
	}

	int get_rent_price_tier1() { return rent_price_tier1; }
	void set_rent_price_tier1(int rent_price_tier1) {
		this->rent_price_tier1 = rent_price_tier1;
	}

	int get_rent_price_tier2() { return rent_price_tier2; }
	void set_rent_price_tier2(int rent_price_tier2) {
		this->rent_price_tier2 = rent_price_tier2;
	}

	int get_rent_price_tier3() { return rent_price_tier3; }
	void set_rent_price_tier3(int rent_price_tier3) {
		this->rent_price_tier3= rent_price_tier3;
	}

	int get_rent_price_tier4() { return rent_price_tier4; }
	void set_rent_price_tier4(int rent_price_tier4) {
		this->rent_price_tier4 = rent_price_tier4;
	}

	int get_home_count() { return home_count; }
	void set_home_count(int home_count) {
		this->home_count = home_count;
	}


};

void chance_card() {

	static int move_pawn = 20;	/* - przesunięcie pionka						*/
	static int payment = 40;	/* - wpłata pieniędzy do banku					*/
	static int withdrawal = 60; /* - otrzymanie pieniędzy						*/
	static int jail = 80;		/* - konieczność pójścia do więzienia			*/
	static int jail_card = 100; /* - możliwość bezpłatnego wyjścia z więzienia  */

	int random_card = rand() % 101;

	if (random_card <= move_pawn) {
		std::cout << "przenieś pionek\n";
	}
	else if (random_card <= payment) {
		std::cout << "płacisz x pieniedzy\n";
	}
	else if (random_card <= withdrawal) {
		std::cout << "otrzymujesz x pieniedzy\n";
	}
	else if (random_card <= jail) {
		std::cout << "idziesz do więzienia\n";
	}
	else if (random_card <= jail_card) {
		std::cout << "dostajesz karte wyjscia z wiezienia\n";
	}

}

int main()
{
	Player player1;
	player1.set_name = 1;
	player1.set_money = 1500;
	player1.set_current_field = 0;

	Player player2;
	player2.set_name = 2;
	player2.set_money = 1500;
	player2.set_current_field = 0;


	srand(time(NULL));

	for(int i=0; i<10;i++) {
		std::cout << throw_bones() << " <-- liczba\n";
	}

	for (int i = 0; i < 10; i++) {
		chance_card();
	}
    
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
