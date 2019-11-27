#include "board.hpp"
#include "field.hpp"
#include <iostream>
#include "propertyfield.hpp"

Board::Board() {
    // tutaj będą tworzone wszystkie elementy typu field, tj miasta, koleje itd.
	Field* field1 = new Field(START, 0);
	fields[0] = field1;



	//Property fields
	//Field* field2 = new Field();
	PropertyField* field2 = new PropertyField(NULL, "Grecja", "Saloniki", 120, new int[10, 40, 120, 360, 640, 900], 0, 100, 60, false, PROPERTY, 1);
	fields[1] = field2;
	//Field* field4 = new Field(PROPERTY, 3);
	PropertyField* field4 = new PropertyField(NULL, "Grecja", "Ateny", 120, new int[10, 40, 120, 360, 640, 900], 0, 100, 60, false, PROPERTY, 3);
	fields[3] = field4;
	//Field* field7 = new Field(PROPERTY, 6);
	PropertyField* field7 = new PropertyField(NULL, "Włochy", "Neapol", 200, new int[15, 60, 180, 540, 800, 1100], 0, 100, 100, false, PROPERTY, 6);
	fields[6] = field7;
	//Field* field9 = new Field(PROPERTY, 8);
	PropertyField* field9 = new PropertyField(NULL, "Włochy", "Mediolan", 200, new int[15, 60, 180, 540, 800, 1100], 0, 100, 100, false, PROPERTY, 8);
	fields[8] = field9;
	//Field* field10 = new Field(PROPERTY, 9);
	PropertyField* field10 = new PropertyField(NULL, "Włochy", "Rzym", 240, new int[20, 80, 200, 600, 900, 1200], 0, 100, 120, false, PROPERTY, 9);
	fields[9] = field10;
	//Field* field12 = new Field(PROPERTY, 11);
	PropertyField* field12 = new PropertyField(NULL, "Hiszpania", "Barcelona", 280, new int[20, 100, 300, 900, 1250, 1500], 0, 200, 140, false, PROPERTY, 11);
	fields[11] = field12;
	//Field* field14 = new Field(PROPERTY, 13);
	PropertyField* field14 = new PropertyField(NULL, "Hiszpania", "Sewilla", 280, new int[20, 100, 300, 900, 1250, 1500], 0, 200, 140, false, PROPERTY, 13);
	fields[13] = field14;
	//Field* field15 = new Field(PROPERTY, 14);
	PropertyField* field15 = new PropertyField(NULL, "Hiszpania", "Madryt", 320, new int[25, 120, 360, 1000, 1400, 1800], 0, 200, 160, false, PROPERTY, 14);
	fields[14] = field15;
	//Field* field17 = new Field(PROPERTY, 16);
	PropertyField* field17 = new PropertyField(NULL, "Wielka Brytania", "Liverpool", 360, new int[30, 140, 400, 1100, 1500, 1900], 0, 200, 180, false, PROPERTY, 16);
	fields[16] = field17;
	//Field* field19 = new Field(PROPERTY, 18);
	PropertyField* field19 = new PropertyField(NULL, "Wielka Brytania", "Glasgow", 360, new int[30, 140, 400, 1100, 1500, 1900], 0, 200, 180, false, PROPERTY, 18);
	fields[18] = field19;
	//Field* field20 = new Field(PROPERTY, 19);
	PropertyField* field20 = new PropertyField(NULL, "Wielka Brytania", "Londyn", 400, new int[35, 160, 440, 1200, 1600, 2000], 0, 200, 200, false, PROPERTY, 19);
	fields[19] = field20;
	//Field* field22 = new Field(PROPERTY, 21);
	PropertyField* field22 = new PropertyField(NULL, "Benelux", "Rotterdam", 440, new int[35, 180, 500, 1400, 1750, 2100], 0, 300, 220, false, PROPERTY, 21);
	fields[21] = field22;
	//Field* field24 = new Field(PROPERTY, 23);
	PropertyField* field24 = new PropertyField(NULL, "Benelux", "Bruksela", 440, new int[35, 180, 500, 1400, 1750, 2100], 0, 300, 220, false, PROPERTY, 23);
	fields[23] = field24;
	//Field* field25 = new Field(PROPERTY, 24);
	PropertyField* field25 = new PropertyField(NULL, "Benelux", "Amsterdam", 480, new int[40, 200, 600, 1500, 1850, 2200], 0, 300, 240, false, PROPERTY, 24);
	fields[24] = field25;
	//Field* field27 = new Field(PROPERTY, 26);
	PropertyField* field27 = new PropertyField(NULL, "Szwecja", "Malmo", 520, new int[45, 220, 660, 1600, 1950, 2300], 0, 300, 260, false, PROPERTY, 26);
	fields[26] = field27;
	//Field* field28 = new Field(PROPERTY, 27);
	PropertyField* field28 = new PropertyField(NULL, "Szwecja", "Goteborg", 520, new int[45, 220, 660, 1600, 1950, 2300], 0, 300, 260, false, PROPERTY, 27);
	fields[27] = field28;
	//Field* field30 = new Field(PROPERTY, 29);
	PropertyField* field30 = new PropertyField(NULL, "Szwecja", "Sztokholm", 560, new int[50, 240, 720, 1700, 2050, 2400], 0, 300, 280, false, PROPERTY, 29);
	fields[29] = field30;
	//Field* field32 = new Field(PROPERTY, 31);
	PropertyField* field32 = new PropertyField(NULL, "Niemcy", "Frankfurt", 600, new int[55, 260, 780, 1900, 2200, 2550], 0, 400, 300, false, PROPERTY, 31);
	fields[31] = field32;
	//Field* field33 = new Field(PROPERTY, 32);
	PropertyField* field33 = new PropertyField(NULL, "Niemcy", "Kolonia", 600, new int[55, 260, 780, 1900, 2200, 2550], 0, 400, 300, false, PROPERTY, 32);
	fields[32] = field33;
	//Field* field35 = new Field(PROPERTY, 34);
	PropertyField* field35 = new PropertyField(NULL, "Niemcy", "Bonn", 640, new int[60, 300, 900, 2000, 2400, 2800], 0, 400, 320, false, PROPERTY, 34);
	fields[34] = field35;
	//Field* field38 = new Field(PROPERTY, 37);
	PropertyField* field38 = new PropertyField(NULL, "Austria", "Innsbruck", 700, new int[70, 350, 1000, 2200, 2600, 3000], 0, 400, 350, false, PROPERTY, 37);
	fields[37] = field38;
	//Field* field40 = new Field(PROPERTY, 39);
	PropertyField* field40 = new PropertyField(NULL, "Austria", "Wiedeń", 800, new int[100, 400, 1200, 2800, 3400, 4000], 0, 400, 400, false, PROPERTY, 39);
	fields[39] = field40;
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