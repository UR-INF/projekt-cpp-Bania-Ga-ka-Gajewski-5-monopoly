#include "field.hpp"
#include <string>

Field::Field(FieldType type, int fieldNumber) {
    this->type = type;
    this->fieldNumber = fieldNumber;
}

Field::~Field() {

}

FieldType Field::getFieldType() {
    return this->type;
}

int Field::getFieldNumber() {
	return this->fieldNumber;
}
void Field::setField(FieldType type, int fieldNumber) {
	this->type = type;
	this->fieldNumber = fieldNumber;
}

std::string Field::toString() {
    std::string fieldNumber = std::to_string(this->getFieldNumber());
    fieldNumber.resize(2, ' ');
    std::string fieldString = "";

    switch(this->getFieldType()) {
        case START:
            fieldString = " - Pole typu START";
            break;
        case JAIL:
            fieldString = " - Pole wiezienia";
            break;
        case GO_TO_JAIL:
            fieldString = " - Pole idziesz do wiezienia";
            break;
        case FREE_PARKING:
            fieldString = " - Pole darmowy parking";
            break;
        case PROPERTY:
            fieldString = " - Pole nieruchomosci ";        
            break;  
        case RAILWAY:
            fieldString = " - Pole koleje";
            break;
        case ELECTRICITY:
            fieldString = " - Pole elektrownia";
            break;
        case WATER_SUPPLY_NETWORK:
            fieldString = " - Pole wodociagi";
            break;
        case INCOME_TAX:
            fieldString = " - Pole podatek dochodowy";
            break;
        case BLUE_CHANCE:
            fieldString = " - Pole szansy - niebieska";
            break;
        case RED_CHANCE:
            fieldString = " - Pole szansy - czerwona";
            break;
        case LUXURY_TAX:
            fieldString = " - Pole podatek od luksusu";
            break;
    }

    fieldString.resize(30, ' ');

    return (fieldNumber + fieldString);
}
