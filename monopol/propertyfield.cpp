#include "propertyfield.hpp"
#include "fieldtype.hpp"

PropertyField::PropertyField(Player* owner, string country, string city, int price, int pricing[], int housingLevel, int upgradeCost, int mortgage, bool isUnderMortgage, FieldType type, int fieldNumer)
                            : Field(type, fieldNumer) {
    this->owner = owner;
    this->country = country;
    this->city = city;
    this->price = price;
    *this->pricing = *pricing;
    this->housingLevel = housingLevel;
    this->upgradeCost = upgradeCost;
    this->mortgage = mortgage;
    this-> isUnderMortgage = isUnderMortgage;
}

PropertyField::~PropertyField() {

}

Player* PropertyField::getOwner() {
    return this->owner;
}

void PropertyField::setOwner(Player* owner) {
    this->owner = owner;
}

int PropertyField::getPrice() {
    return this->price;
}

void PropertyField::upgrade() {
    if (this->housingLevel == 5)
        return;

    this->housingLevel++;
}

void PropertyField::degrade() {
    if (this->housingLevel == 0)
        return;

    this->housingLevel--;
}

int PropertyField::getCurrentRent() {
    return this->pricing[this->housingLevel];
}

void PropertyField::setMortgage(bool mortgage) {
    this->isUnderMortgage = mortgage;
}

string PropertyField::getPropertyInfo() {
    return this->country + " - " + this->city; 
}

string PropertyField::toString() {
    string fieldNumber = to_string(this->getFieldNumber());
    string fieldString = fieldNumber + " - " + this->country + " - " + this->city;

    if (this->getOwner()) {
        fieldString += " - Wlasciciel: " + this->getOwner()->getName();
    }
    else {
        fieldString += " - Wlasciciel: brak";
    }

    return fieldString;
}