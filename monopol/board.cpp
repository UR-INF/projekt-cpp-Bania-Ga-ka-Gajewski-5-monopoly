#include "board.hpp"
#include "field.hpp"
#include "purchasablefield.hpp"
#include "propertyfield.hpp"
#include "railwayfield.hpp"
#include "rentmultipierfield.hpp"
#include "country.hpp"
#include <iostream>
#include <time.h>
#include <set>
#include <vector> 
#include <algorithm>

int myrandom(int i) { return std::rand() % i; };

Board::Board() {
	srand(unsigned(time(0)));
    // tutaj będą tworzone wszystkie elementy typu field, tj miasta, koleje itd.
	Field* field1 = new Field(START, 0);
	fields[0] = field1;
	//Field* field2 = new Field();
	PropertyField* field2 = new PropertyField("Grecja", "Saloniki", new int[6] {10, 40, 120, 360, 640, 900}, 0, 100, NULL, 120, 10, 60, PROPERTY, 1);
	fields[1] = field2;
	Field* field3 = new Field(BLUE_CHANCE,2);
	fields[2] = field3;
	//Field* field4 = new Field(PROPERTY, 3);
	PropertyField* field4 = new PropertyField("Grecja", "Ateny", new int[6] {10, 40, 120, 360, 640, 900}, 0, 100, NULL, 120, 10, 60, PROPERTY, 3);
	fields[3] = field4;
	Field* field5 = new Field(INCOME_TAX, 4);
	fields[4] = field5;
	// Field* field6 = new Field(RAILWAY, 5);
	Field* field6 = new RailwayField("Koleje poludniowe", NULL, 400, 50, 200, RAILWAY, 5);
	fields[5] = field6;
	//Field* field7 = new Field(PROPERTY, 6);
	PropertyField* field7 = new PropertyField("Wlochy", "Neapol", new int[6]{15, 60, 180, 540, 800, 1100}, 0, 100, NULL, 200, 15, 100, PROPERTY, 6);
	fields[6] = field7;
	Field* field8 = new Field(RED_CHANCE, 7);
	fields[7] = field8;
	//Field* field9 = new Field(PROPERTY, 8);
	PropertyField* field9 = new PropertyField("Wlochy", "Mediolan", new int[6]{15, 60, 180, 540, 800, 1100}, 0, 100, NULL, 200, 15, 100, PROPERTY, 8);
	fields[8] = field9;
	//Field* field10 = new Field(PROPERTY, 9);
	PropertyField* field10 = new PropertyField("Wlochy", "Rzym", new int[6] {20, 80, 200, 600, 900, 1200}, 0, 100, NULL, 240, 20, 120, PROPERTY, 9);
	fields[9] = field10;
	Field* field11 = new Field(JAIL, 10);
	fields[10] = field11;
	//Field* field12 = new Field(PROPERTY, 11);
	PropertyField* field12 = new PropertyField("Hiszpania", "Barcelona", new int[6]{20, 100, 300, 900, 1250, 1500}, 0, 200, NULL, 280, 20, 140, PROPERTY, 11);
	fields[11] = field12;
	// Field* field13 = new Field(ELECTRICITY, 12);
	Field* field13 = new RentMultipierField("Elektrownia", NULL, 300, 10, 150, ELECTRICITY, 12);
	fields[12] = field13;
	//Field* field14 = new Field(PROPERTY, 13);
	PropertyField* field14 = new PropertyField("Hiszpania", "Sewilla", new int[6]{20, 100, 300, 900, 1250, 1500}, 0, 200, NULL, 280, 20, 140, PROPERTY, 13);
	fields[13] = field14;
	//Field* field15 = new Field(PROPERTY, 14);
	PropertyField* field15 = new PropertyField("Hiszpania", "Madryt", new int[6]{25, 120, 360, 1000, 1400, 1800}, 0, 200, NULL, 320, 25, 160, PROPERTY, 14);
	fields[14] = field15;
	// Field* field16 = new Field(RAILWAY, 15);
	Field* field16 = new RailwayField("Koleje zachodnie", NULL,  400, 50, 200, RAILWAY, 15);
	fields[15] = field16;
	//Field* field17 = new Field(PROPERTY, 16);
	PropertyField* field17 = new PropertyField("Wielka Brytania", "Liverpool", new int[6]{30, 140, 400, 1100, 1500, 1900}, 0, 200, NULL, 360, 30, 180, PROPERTY, 16);
	fields[16] = field17;
	Field* field18 = new Field(BLUE_CHANCE, 17);
	fields[17] = field18;
	//Field* field19 = new Field(PROPERTY, 18);
	PropertyField* field19 = new PropertyField("Wielka Brytania", "Glasgow", new int[6]{30, 140, 400, 1100, 1500, 1900}, 0, 200, NULL, 360, 30, 180, PROPERTY, 18);
	fields[18] = field19;
	//Field* field20 = new Field(PROPERTY, 19);
	PropertyField* field20 = new PropertyField("Wielka Brytania", "Londyn", new int[6]{35, 160, 440, 1200, 1600, 2000}, 0, 200, NULL,  400, 35, 200, PROPERTY, 19);
	fields[19] = field20;
	Field* field21 = new Field(FREE_PARKING, 20);
	fields[20] = field21;
	//Field* field22 = new Field(PROPERTY, 21);
	PropertyField* field22 = new PropertyField("Benelux", "Rotterdam", new int[6]{35, 180, 500, 1400, 1750, 2100}, 0, 300, NULL, 440, 35, 220, PROPERTY, 21);
	fields[21] = field22;
	Field* field23 = new Field(RED_CHANCE, 22);
	fields[22] = field23;
	//Field* field24 = new Field(PROPERTY, 23);
	PropertyField* field24 = new PropertyField("Benelux", "Bruksela", new int[6]{35, 180, 500, 1400, 1750, 2100}, 0, 300, NULL, 440, 35, 220, PROPERTY, 23);
	fields[23] = field24;
	//Field* field25 = new Field(PROPERTY, 24);
	PropertyField* field25 = new PropertyField("Benelux", "Amsterdam", new int[6]{40, 200, 600, 1500, 1850, 2200}, 0, 300, NULL, 480, 40, 240, PROPERTY, 24);
	fields[24] = field25;
	// Field* field26 = new Field(RAILWAY, 25);
	Field* field26 = new RailwayField("Koleje polnocne", NULL, 400, 50, 200, RAILWAY, 25);
	fields[25] = field26;
	//Field* field27 = new Field(PROPERTY, 26);
	PropertyField* field27 = new PropertyField("Szwecja", "Malmo", new int[6]{45, 220, 660, 1600, 1950, 2300}, 0, 300, NULL, 520, 45, 260, PROPERTY, 26);
	fields[26] = field27;
	//Field* field28 = new Field(PROPERTY, 27);
	PropertyField* field28 = new PropertyField("Szwecja", "Goteborg", new int[6]{45, 220, 660, 1600, 1950, 2300}, 0, 300, NULL, 520, 45, 260, PROPERTY, 27);
	fields[27] = field28;
	// Field* field29 = new Field(WATER_SUPPLY_NETWORK, 28);
	Field* field29 = new RentMultipierField("Wodociagi", NULL, 300, 10, 150, WATER_SUPPLY_NETWORK, 28);
	fields[28] = field29;
	//Field* field30 = new Field(PROPERTY, 29);
	PropertyField* field30 = new PropertyField("Szwecja", "Sztokholm", new int[6]{50, 240, 720, 1700, 2050, 2400}, 0, 300, NULL, 560, 50, 280, PROPERTY, 29);
	fields[29] = field30;
	Field* field31 = new Field(GO_TO_JAIL, 30);
	fields[30] = field31;
	//Field* field32 = new Field(PROPERTY, 31);
	PropertyField* field32 = new PropertyField("Niemcy", "Frankfurt", new int[6]{55, 260, 780, 1900, 2200, 2550}, 0, 400, NULL, 600, 55, 300, PROPERTY, 31);
	fields[31] = field32;
	//Field* field33 = new Field(PROPERTY, 32);
	PropertyField* field33 = new PropertyField("Niemcy", "Kolonia", new int[6]{55, 260, 780, 1900, 2200, 2550}, 0, 400, NULL, 600, 55, 300, PROPERTY, 32);
	fields[32] = field33;
	Field* field34 = new Field(BLUE_CHANCE, 33);
	fields[33] = field34;
	//Field* field35 = new Field(PROPERTY, 34);
	PropertyField* field35 = new PropertyField("Niemcy", "Bonn", new int[6]{60, 300, 900, 2000, 2400, 2800}, 0, 400, NULL, 640, 60, 320, PROPERTY, 34);
	fields[34] = field35;
	// Field* field36 = new Field(RAILWAY, 35);
	Field* field36 = new RailwayField("Koleje wschodnie", NULL, 400, 50, 200, RAILWAY, 35);
	fields[35] = field36;
	Field* field37 = new Field(RED_CHANCE, 36);
	fields[36] = field37;
	//Field* field38 = new Field(PROPERTY, 37);
	PropertyField* field38 = new PropertyField("Austria", "Innsbruck", new int[6]{70, 350, 1000, 2200, 2600, 3000}, 0, 400, NULL, 700, 70, 350, PROPERTY, 37);
	fields[37] = field38;
	Field* field39 = new Field(LUXURY_TAX, 38);
	fields[38] = field39;
	//Field* field40 = new Field(PROPERTY, 39);
	PropertyField* field40 = new PropertyField("Austria", "Wieden", new int[6]{100, 400, 1200, 2800, 3400, 4000}, 0, 400, NULL, 800, 100, 400, PROPERTY, 39);
	fields[39] = field40;
	bool test = testFields();
	cout << "Test Planszy: " << test << endl;


	// **************************************************************************************************************
	//inicjalizacja kart
	vector<Card> tempBlueCards;
	//karty niebieskie
	Card blue0 =  Card(0, "Wychodzisz wolny z wiezienia. Karte nalezy zachowac do wykorzystania lub sprzedania.");
	//blueCards[0] = blue0;
	tempBlueCards.push_back(blue0);

	Card blue1 =  Card(1, "Wracasz do \"WIEDNIA\"");
	//blueCards[1] = blue1;
	tempBlueCards.push_back(blue1);

	Card blue2 =  Card(2, "Placisz za karte 20$ lub ciagniesz \"SZANSE\" z drugiego zestawu (czerwonego)");
	//blueCards[2] = blue2;
	tempBlueCards.push_back(blue2);

	Card blue3 =  Card(3, "Wracasz na \"START\"");
	//blueCards[3] = blue3;
	tempBlueCards.push_back(blue3);

	Card blue4 =  Card(4, "Idziesz do wiezienia. Nie przechodzisz przez \"START\". Nie otrzymujesz 200$.");
	//blueCards[4] = blue4;
	tempBlueCards.push_back(blue4);

	Card blue5 =  Card(5, "Placisz koszty leczenia w wysokosci 20$.");
	//blueCards[5] = blue5;
	tempBlueCards.push_back(blue5);

	Card blue6 =  Card(6, "Bank omylil sie na Twoja krozysc. Otrzymujesz 400$.");
	//blueCards[6] = blue6;
	tempBlueCards.push_back(blue6);

	Card blue7 =  Card(7, "Zajales II miejsce w konkursie pieknosci - otrzymujesz z banku 200$.");
	//blueCards[7] = blue7;
	tempBlueCards.push_back(blue7);

	Card blue8 =  Card(8, "Otrzymujesz roczna rente w wysokosci 200$.");
	//blueCards[8] = blue8;
	tempBlueCards.push_back(blue8);

	Card blue9 =  Card(9, "Bank wyplaci ci nalezne 7% od kapitalow - otrzymujesz 50$.");
	//blueCards[9] = blue9;
	tempBlueCards.push_back(blue9);

	Card blue10 =  Card(10, "Placisz skladke ubezpieczeniowa w wysokosci 20$.");
	//blueCards[10] = blue10;
	tempBlueCards.push_back(blue10);

	Card blue11 =  Card(11, "Z magazynu, w ktorym kupujesz otrzymujesz rabat w wyoskosci 20$.");
	//blueCards[11] = blue11;
	tempBlueCards.push_back(blue11);

	Card blue12 =  Card(12, "Placisz na budowe szpitala 400$.");
	//blueCards[12] = blue12;
	tempBlueCards.push_back(blue12);

	Card blue13 =  Card(13, "Otrzymujesz w spadku 200$.");
	//blueCards[13] = blue13;
	tempBlueCards.push_back(blue13);

	Card blue14 =  Card(14, "Masz urodziny - otrzymujesz od kazdego gracza po 20$.");
	//blueCards[14] = blue14;
	tempBlueCards.push_back(blue14);


	vector<Card> tempRedCards;
	//karty czerwone
	Card red0 =  Card(0, "Wracasz na \"START\"");
	//redCards[0] = red0;
	tempRedCards.push_back(red0);

	Card red1 =  Card(1, "Piles w czasie pracy, placisz kare 40$.");
	//redCards[1] = red1;
	tempRedCards.push_back(red1);

	Card red2 =  Card(2, "Idziesz do wiezienia. Nie przechodzisz przez \"START\". Nie otrzymujesz premii 200$.");
	//redCards[2] = red2;
	tempRedCards.push_back(red2);

	Card red3 =  Card(3, "Remontujesz swoje domy. Placisz do banku za kazdy dom 50$, za kazdy hotel 200$.");
	//redCards[3] = red3;
	tempRedCards.push_back(red3);
	
	Card red4 =  Card(4, "Cofasz sie o 3 pola.");
	//redCards[4] = red4;
	tempRedCards.push_back(red4);

	Card red5 =  Card(5, "Wcyhodzisz wolny z wiezienia. Karte nalezy zachowac do wykorzystania lub sprzedania.");
	//redCards[5] = red5;
	tempRedCards.push_back(red5);

	Card red6 =  Card(6, "Idziesz do \"NEAPOLU\". Jezeli przechodzisz przez \"START\" otrzymasz 200$.");
	//redCards[6] = red6;
	tempRedCards.push_back(red6);

	Card red7 =  Card(7, "Wracasz do \"Madrytu\"");
	//redCards[7] = red7;
	tempRedCards.push_back(red7);

	Card red8 =  Card(8, "Zobowiazany jestes zmodernizowac swoje miasto, placisz do banku za kazdy dom 80$, za kazdy hotel 230$.");
	//redCards[8] = red8;
	tempRedCards.push_back(red8);

	Card red9 =  Card(9, "Idziesz do \"KOLEI WSCHODNICH\". Jezeli przechodzisz przez \"START\" otrzymasz 200$.");
	//redCards[9] = red9;
	tempRedCards.push_back(red9);

	Card red10 =  Card(10, "Wracasz do \"Brukseli\". Jezeli przechodzisz przez \"START\" otrzymujesz 200$.");
	//redCards[10] = red10;
	tempRedCards.push_back(red10);

	Card red11 =  Card(11, "Bank wplaca Ci nalezne odsetkiw  wysokosci 300$.");
	//redCards[11] = red11;
	tempRedCards.push_back(red11);

	Card red12 =  Card(12, "Mandat za szybka jazde. Placisz 30$.");
	//redCards[12] = red12;
	tempRedCards.push_back(red12);

	Card red13 =  Card(13, "Placisz oplate za szkole 300$.");
	//redCards[13] = red13;
	tempRedCards.push_back(red13);

	Card red14 =  Card(14, "Bank wyplaca Ci pprocent w wysokosci 100$.");
	//redCards[14] = red14;
	tempRedCards.push_back(red14);

	Card red15 =  Card(15, "Rozwiazales dobrze krzyzowke. Jako I nagrode otrzymujesz 200$.");
	//redCards[15] = red15;
	tempRedCards.push_back(red15);

	std::random_shuffle(tempBlueCards.begin(), tempBlueCards.end());
	std::random_shuffle(tempRedCards.begin(), tempRedCards.end());

	for (Card card : tempBlueCards) {
		blueCards.push_back(card);
	}

	for (Card card : tempRedCards) {
		redCards.push_back(card);
	}

	

	// shuffleCards(blueCards, 15);
	// shuffleCards(redCards, 16);

	// ***************************************************************************************
	// inicjalizacja panstw
	Country* country1 = new Country("Grecja", set<int> {1, 3});
	Country* country2 = new Country("Wlochy", set<int> {6, 8, 9});
	Country* country3 = new Country("Hiszpania", set<int> {11, 13, 14});
	Country* country4 = new Country("Wielka Brytania", set<int> {16, 18, 19});
	Country* country5 = new Country("Benelux", set<int> {21, 23, 24});
	Country* country6 = new Country("Szwecja", set<int> {26, 27, 29});
	Country* country7 = new Country("Niemcy", set<int> {31, 32, 34});
	Country* country8 = new Country("Austria", set<int> {37, 39});

	this->countries.insert(pair<string, Country*>("Grecja", country1));
	this->countries.insert(pair<string, Country*>("Wlochy", country2));
	this->countries.insert(pair<string, Country*>("Hiszpania", country3));
	this->countries.insert(pair<string, Country*>("Wielka Brytania", country4));
	this->countries.insert(pair<string, Country*>("Benelux", country5));
	this->countries.insert(pair<string, Country*>("Szwecja", country6));
	this->countries.insert(pair<string, Country*>("Niemcy", country7));
	this->countries.insert(pair<string, Country*>("Austria", country8));

	/*
	for (map<string, Country*>::iterator it = this->countries.begin();
		 it != this->countries.end(); ++it) {
			 cout << it->first << endl;
			 for (auto elem : it->second->getProperties()) {
				cout << this->fields[elem]->toString() << endl;
			}
		 }
		 */
}

Board::~Board() {
    std::cout << "Usuwam obiekt Board" << endl;
}

Field* Board::getField(int index) {
    return this->fields[index];
}

void Board::setField(int index, Field* field) {
	this->fields[index] = field;
}

void Board::render() {
    std::cout << "Renderuje plansze" << endl;
}

bool Board::testFields() {
	int badFields = 0;
	int iterator = 0;
	for (Field* field : fields) {
		int fieldNumber = field->getFieldNumber();
		if (fieldNumber != iterator) {
			badFields++;
		}
		
		++iterator;
	}
	if (badFields > 0) {
		return false;
	}
	else
	{
		return true;
	}
}

/*void Board::shuffleCards(Card** cards, int count) {
	std::srand(time(NULL));
	for (int i = count - 1; i > 0; i--) {
		int j = rand() % (i + 1); // wybierz element 0 <= j <= i
		Card* tmp = cards[j]; // zamień cards[i] z cards[j]
		cards[j] = cards[i];
		cards[i] = tmp;
	}
}*/



Card Board::pickBlueCard() {
	Card pickedCard = blueCards.front();
	blueCards.pop_front();
	blueCards.push_back(pickedCard);
	return pickedCard;
}

Card Board::pickRedCard() {
	Card pickedCard = redCards.front();
	redCards.pop_front();
	redCards.push_back(pickedCard);
	return pickedCard;
}

map<string, Country*> Board::getCountries() {
	return this->countries;
}

void Board::setCountries(map<string, Country*> countries) {
	this->countries = countries;
}

Country* Board::getCountry(string name) {
	return this->countries.find(name)->second;
}

void Board::setCountry(string name, Country* country) {
	this->countries.insert(pair<string, Country*>(name, country));
}