#include "railwayfield.hpp"

RailwayField::RailwayField(string name, Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber) : PurchasableField(owner, price, rent, mortgage, type, fieldNumber) {
    this->setOwner(owner);
    this->setName(name);
    this->setPrice(price);
    this->setRent(rent);
    this->setMortgage(mortgage);
    this->setIsMortgaged(false);
}

RailwayField::~RailwayField() {

}

string RailwayField::getName() {
    return this->name;
}

void RailwayField::setName(string name) {
    this->name = name;
}

string RailwayField::toString() {
    string fieldNumber = to_string(this->getFieldNumber());
    string fieldString = fieldNumber + " - " + this->getName();

    if (this->getOwner()) {
        fieldString += " - Wlasciciel: " + this->getOwner()->getName();
    }
    else {
        fieldString += " - Wlasciciel: brak";
    }

    return fieldString;
}