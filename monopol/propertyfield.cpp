#include "propertyfield.hpp"
#include "fieldtype.hpp"
#include <iostream>
#include <vector>

PropertyField::PropertyField(string country, string city, int pricing[], int housingLevel, int upgradeCost, Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber)
                            : PurchasableField(owner, price, rent, mortgage, type, fieldNumber) {
    this->country = country;
    this->city = city;
    this->housingLevel = housingLevel;
    this->upgradeCost = upgradeCost;

    for (int index = 0; index < 6; index++) {
        this->pricing[index] = pricing[index];
    }
}

PropertyField::~PropertyField() {

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

int PropertyField::getRent() {
    return this->pricing[this->housingLevel];
}

string PropertyField::getPropertyInfo() {
    return this->country + " - " + this->city; 
}

string PropertyField::toString() {
    string fieldNumber = to_string(this->getFieldNumber());
    string fieldCountry = this->country;
    string fieldCity = this->city;
    string fieldLevel = to_string(this->getHousingLevel());

    fieldNumber.resize(2, ' ');
    fieldCountry.resize(15, ' ');
    fieldCity.resize(15, ' ');
    
    string fieldString = fieldNumber + " - " + fieldCountry + " - " + fieldCity;

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
    fieldLevel = " - Poziom rozbudowy: " + fieldLevel;

    fieldString += fieldLevel;
     
    return fieldString;
}

string PropertyField::getCountryName() {
    return this->country;
}

int PropertyField::getUpgradeCost() {
    return this->upgradeCost;
}

int PropertyField::getHousingLevel() {
    return this->housingLevel;
}

string PropertyField::getShortName() {
    return this->getPropertyInfo();
}