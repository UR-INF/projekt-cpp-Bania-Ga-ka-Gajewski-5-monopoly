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

int RailwayField::getRent(set<int> properties) {
    // indeksy pol kolei : 5, 15, 25, 35
    int railwaysCount = 0;

    for (auto elem : properties) {
        if (elem == 5 || elem == 15 || elem == 25 || elem == 35) {
            railwaysCount++;
        }
    }

    switch(railwaysCount) {
        case 1:
            return 50;
        case 2:
            return 100;
        case 3:
            return 200;
        case 4:
            return 400;
        default:
            return PurchasableField::getRent();
    }
}

string RailwayField::toString() {
    string fieldNumber = to_string(this->getFieldNumber());
    string fieldName = this->getName();
    fieldNumber.resize(2, ' ');
    fieldName.resize(33, ' ');
    
    string fieldString = fieldNumber + " - " + fieldName;

    if (this->getOwner()) {
        string fieldOwner = this->getOwner()->getName();
        fieldOwner.resize(20, ' ');
        fieldString += " - Wlasciciel: " + fieldOwner;
    }
    else {
        string fieldOwner = "brak";
        fieldOwner.resize(20, ' ');
        fieldString += " - Wlasciciel: " + fieldOwner;
    }

    return fieldString;
}

string RailwayField::getShortName() {
    return this->getName();
}