#include "board.hpp"
#include "field.hpp"
#include <iostream>
#include "propertyfield.hpp"

Board::Board() {
    // tutaj będą tworzone wszystkie elementy typu field, tj miasta, koleje itd.
	Field* field1 = new Field(START, 0);
	fields[0] = field1;
	//Field* field2 = new Field();
	PropertyField* field2 = new PropertyField(NULL, "Grecja", "Saloniki", 120, new int[10, 40, 120, 360, 640, 900], 0, 100, 60, false, PROPERTY, 1);
	fields[1] = field2;
	Field* field3 = new Field(BLUE_CHANCE,2);
	fields[2] = field3;
	//Field* field4 = new Field(PROPERTY, 3);
	PropertyField* field4 = new PropertyField(NULL, "Grecja", "Ateny", 120, new int[10, 40, 120, 360, 640, 900], 0, 100, 60, false, PROPERTY, 3);
	fields[3] = field4;
	Field* field5 = new Field(FREE_PARKING, 4);
	fields[4] = field5;
	Field* field6 = new Field(RAILWAY, 5);
	fields[5] = field6;
	//Field* field7 = new Field(PROPERTY, 6);
	PropertyField* field7 = new PropertyField(NULL, "Włochy", "Neapol", 200, new int[15, 60, 180, 540, 800, 1100], 0, 100, 100, false, PROPERTY, 6);
	fields[6] = field7;
	Field* field8 = new Field(RED_CHANCE, 7);
	fields[7] = field8;
	//Field* field9 = new Field(PROPERTY, 8);
	PropertyField* field9 = new PropertyField(NULL, "Włochy", "Mediolan", 200, new int[15, 60, 180, 540, 800, 1100], 0, 100, 100, false, PROPERTY, 8);
	fields[8] = field9;
	//Field* field10 = new Field(PROPERTY, 9);
	PropertyField* field10 = new PropertyField(NULL, "Włochy", "Rzym", 240, new int[20, 80, 200, 600, 900, 1200], 0, 100, 120, false, PROPERTY, 9);
	fields[9] = field10;
	Field* field11 = new Field(JAIL, 10);
	fields[10] = field11;
	//Field* field12 = new Field(PROPERTY, 11);
	PropertyField* field12 = new PropertyField(NULL, "Hiszpania", "Barcelona", 280, new int[20, 100, 300, 900, 1250, 1500], 0, 200, 140, false, PROPERTY, 11);
	fields[11] = field12;
	Field* field13 = new Field(ELECTRICITY, 12);
	fields[12] = field13;
	//Field* field14 = new Field(PROPERTY, 13);
	PropertyField* field14 = new PropertyField(NULL, "Hiszpania", "Sewilla", 280, new int[20, 100, 300, 900, 1250, 1500], 0, 200, 140, false, PROPERTY, 13);
	fields[13] = field14;
	//Field* field15 = new Field(PROPERTY, 14);
	PropertyField* field15 = new PropertyField(NULL, "Hiszpania", "Madryt", 320, new int[25, 120, 360, 1000, 1400, 1800], 0, 200, 160, false, PROPERTY, 14);
	fields[14] = field15;
	Field* field16 = new Field(RAILWAY, 15);
	fields[15] = field16;
	//Field* field17 = new Field(PROPERTY, 16);
	PropertyField* field17 = new PropertyField(NULL, "Wielka Brytania", "Liverpool", 360, new int[30, 140, 400, 1100, 1500, 1900], 0, 200, 180, false, PROPERTY, 16);
	fields[16] = field17;
	Field* field18 = new Field(BLUE_CHANCE, 17);
	fields[17] = field18;
	//Field* field19 = new Field(PROPERTY, 18);
	PropertyField* field19 = new PropertyField(NULL, "Wielka Brytania", "Glasgow", 360, new int[30, 140, 400, 1100, 1500, 1900], 0, 200, 180, false, PROPERTY, 18);
	fields[18] = field19;
	//Field* field20 = new Field(PROPERTY, 19);
	PropertyField* field20 = new PropertyField(NULL, "Wielka Brytania", "Londyn", 400, new int[35, 160, 440, 1200, 1600, 2000], 0, 200, 200, false, PROPERTY, 19);
	fields[19] = field20;
	Field* field21 = new Field(INCOME_TAX, 20);
	fields[20] = field21;
	//Field* field22 = new Field(PROPERTY, 21);
	PropertyField* field22 = new PropertyField(NULL, "Benelux", "Rotterdam", 440, new int[35, 180, 500, 1400, 1750, 2100], 0, 300, 220, false, PROPERTY, 21);
	fields[21] = field22;
	Field* field23 = new Field(RED_CHANCE, 22);
	fields[22] = field23;
	//Field* field24 = new Field(PROPERTY, 23);
	PropertyField* field24 = new PropertyField(NULL, "Benelux", "Bruksela", 440, new int[35, 180, 500, 1400, 1750, 2100], 0, 300, 220, false, PROPERTY, 23);
	fields[23] = field24;
	//Field* field25 = new Field(PROPERTY, 24);
	PropertyField* field25 = new PropertyField(NULL, "Benelux", "Amsterdam", 480, new int[40, 200, 600, 1500, 1850, 2200], 0, 300, 240, false, PROPERTY, 24);
	fields[24] = field25;
	Field* field26 = new Field(RAILWAY, 25);
	fields[25] = field26;
	//Field* field27 = new Field(PROPERTY, 26);
	PropertyField* field27 = new PropertyField(NULL, "Szwecja", "Malmo", 520, new int[45, 220, 660, 1600, 1950, 2300], 0, 300, 260, false, PROPERTY, 26);
	fields[26] = field27;
	//Field* field28 = new Field(PROPERTY, 27);
	PropertyField* field28 = new PropertyField(NULL, "Szwecja", "Goteborg", 520, new int[45, 220, 660, 1600, 1950, 2300], 0, 300, 260, false, PROPERTY, 27);
	fields[27] = field28;
	Field* field29 = new Field(WATER_SUPPLY_NETWORK, 28);
	fields[28] = field29;
	//Field* field30 = new Field(PROPERTY, 29);
	PropertyField* field30 = new PropertyField(NULL, "Szwecja", "Sztokholm", 560, new int[50, 240, 720, 1700, 2050, 2400], 0, 300, 280, false, PROPERTY, 29);
	fields[29] = field30;
	Field* field31 = new Field(GO_TO_JAIL, 30);
	fields[30] = field31;
	//Field* field32 = new Field(PROPERTY, 31);
	PropertyField* field32 = new PropertyField(NULL, "Niemcy", "Frankfurt", 600, new int[55, 260, 780, 1900, 2200, 2550], 0, 400, 300, false, PROPERTY, 31);
	fields[31] = field32;
	//Field* field33 = new Field(PROPERTY, 32);
	PropertyField* field33 = new PropertyField(NULL, "Niemcy", "Kolonia", 600, new int[55, 260, 780, 1900, 2200, 2550], 0, 400, 300, false, PROPERTY, 32);
	fields[32] = field33;
	Field* field34 = new Field(BLUE_CHANCE, 33);
	fields[33] = field34;
	//Field* field35 = new Field(PROPERTY, 34);
	PropertyField* field35 = new PropertyField(NULL, "Niemcy", "Bonn", 640, new int[60, 300, 900, 2000, 2400, 2800], 0, 400, 320, false, PROPERTY, 34);
	fields[34] = field35;
	Field* field36 = new Field(RAILWAY, 35);
	fields[35] = field36;
	Field* field37 = new Field(RED_CHANCE, 36);
	fields[36] = field37;
	//Field* field38 = new Field(PROPERTY, 37);
	PropertyField* field38 = new PropertyField(NULL, "Austria", "Innsbruck", 700, new int[70, 350, 1000, 2200, 2600, 3000], 0, 400, 350, false, PROPERTY, 37);
	fields[37] = field38;
	Field* field39 = new Field(LUXURY_TAX, 38);
	fields[38] = field39;
	//Field* field40 = new Field(PROPERTY, 39);
	PropertyField* field40 = new PropertyField(NULL, "Austria", "Wiedeń", 800, new int[100, 400, 1200, 2800, 3400, 4000], 0, 400, 400, false, PROPERTY, 39);
	fields[39] = field40;
	bool test = testFields();
	cout << "Test Planszy: " << test << endl;


	//inicjalizacja kart

	//karty niebieskie
	Card* blue0 = new Card(0, "Wychodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.");
	blueCards[0] = blue0;

	Card* blue1 = new Card(1, "Wracasz do \"WIEDNIA\"");
	blueCards[1] = blue1;

	Card* blue2 = new Card(2, "Płacisz za kartę 20$ lub ciągniesz \"SZANSĘ\" z drugiego zestawu (czerwonego)");
	blueCards[2] = blue2;

	Card* blue3 = new Card(3, "Wracasz na \"START\"");
	blueCards[3] = blue3;

	Card* blue4 = new Card(4, "Idziesz do więzienia. Nie przechodzisz przez \"START\". Nie otrzymujesz 200$.");
	blueCards[4] = blue4;

	Card* blue5 = new Card(5, "Płacisz koszty leczenia w wysokości 20$.");
	blueCards[5] = blue5;

	Card* blue6 = new Card(6, "Bank omylił się na Twoją krozyść. Otrzymujesz 400$.");
	blueCards[6] = blue6;

	Card* blue7 = new Card(7, "Zająłeś II miejsce w konkursie piękności - otrzymujesz z banku 200$.");
	blueCards[7] = blue7;

	Card* blue8 = new Card(8, "Otrzymujesz roczną rentę w wysokości 200$.");
	blueCards[8] = blue8;

	Card* blue9 = new Card(9, "Bank wypłaci ci należne 7% od kapitałów - otrzymujesz 50$.");
	blueCards[9] = blue9;

	Card* blue10 = new Card(10, "Płacisz składkę ubezpieczeniową w wysokości 20$.");
	blueCards[10] = blue10;

	Card* blue11 = new Card(11, "Z magazynu, w którym kupujesz otrzymujesz rabat w wyoskości 20$.");
	blueCards[11] = blue11;

	Card* blue12 = new Card(12, "Płacisz na budowę szpitala 400$.");
	blueCards[12] = blue12;

	Card* blue13 = new Card(13, "Otrzymujesz w spadku 200$.");
	blueCards[13] = blue13;

	Card* blue14 = new Card(14, "Masz urodziny - otrzymujesz od każdego gracza po 20$.");
	blueCards[14] = blue14;

	//karty czerwone
	Card* red0 = new Card(0, "Wracasz na \"START\"");
	redCards[0] = red0;

	Card* red1 = new Card(1, "Piłeś w czasie pracy, płacisz karę 40$.");
	redCards[1] = red1;

	Card* red2 = new Card(2, "Idziesz do więzienia. Nie przechodzisz przez \"START\". Nie otrzymujesz premii 200$.");
	redCards[2] = red2;

	Card* red3 = new Card(3, "Remontujesz swoje domy. Płacisz do banku za każdy dom 50$, za każdy hotel 200$.");
	redCards[3] = red3;
	
	Card* red4 = new Card(4, "Cofasz się o 3 pola.");
	redCards[4] = red4;

	Card* red5 = new Card(5, "Wcyhodzisz wolny z więzienia. Kartę należy zachować do wykorzystania lub sprzedania.");
	redCards[5] = red5;

	Card* red6 = new Card(6, "Idziesz do \"NEAPOLU\". Jeżeli przechodzisz przez \"START\" otrzymasz 200$.");
	redCards[6] = red6;

	Card* red7 = new Card(7, "Wracasz do \"Madrytu\"");
	redCards[7] = red7;

	Card* red8 = new Card(8, "Zobowiązany jesteś zmodernizować swoje miasto, płacisz do banku za każdy dom 80$, za każdy hotel 230$.");
	redCards[8] = red8;

	Card* red9 = new Card(9, "Idziesz do \"KOLEI WSCHODNICH\". Jeżeli przechodzisz przez \"START\" otrzymasz 200$.");
	redCards[9] = red9;

	Card* red10 = new Card(10, "Wracasz do \"Brukseli\". Jeżeli przechodzisz przez \"START\" otrzymujesz 200$.");
	redCards[10] = red10;

	Card* red11 = new Card(11, "Bank wpłaca Ci należne odsetkiw  wysokości 300$.");
	redCards[11] = red11;

	Card* red12 = new Card(12, "Mandat za szybką jazdę. Płacisz 30$.");
	redCards[12] = red12;

	Card* red13 = new Card(13, "Płacisz opłatę za szkołę 300$.");
	redCards[13] = red13;

	Card* red14 = new Card(14, "Bank wypłaca Ci pprocent w wysokości 100$.");
	redCards[14] = red14;

	Card* red15 = new Card(15, "Rozwiązałeś dobrze krzyżówkę. Jako I nagrodę otrzymujesz 200$.");
	redCards[15] = red15;

}

Board::~Board() {

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