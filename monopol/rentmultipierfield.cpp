#include "rentmultipierfield.hpp"

using namespace std;

RentMultipierField::RentMultipierField(string name, Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber)
                                : PurchasableField(owner, price, rent, mortgage, type, fieldNumber) {
    this->setName(name);
}

RentMultipierField::~RentMultipierField() {
    
}

string RentMultipierField::getName() {
    return this->name;
}

void RentMultipierField::setName(string name) {
    this->name = name;
}

int RentMultipierField::getRent() {
    return PurchasableField::getRent();
}

string RentMultipierField::toString() {
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

string RentMultipierField::getShortName() {
    return this->name;
}