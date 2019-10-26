#include "propertyfield.hpp"

PropertyField::PropertyField(Player* owner, string country, string city, int price, int pricing[], int housingLevel, int upgradeCost, int mortgage, bool isUnderMortgage) {
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

void PropertyField::setOwner(Player* owner) {
    this->owner = owner;
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