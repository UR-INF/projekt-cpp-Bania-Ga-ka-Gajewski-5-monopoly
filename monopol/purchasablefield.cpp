#include "purchasablefield.hpp"

PurchasableField::PurchasableField(Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber) : Field(type, fieldNumber){
    this->setOwner(owner);
    this->setPrice(price);
    this->setRent(rent);
    this->setMortgage(mortgage);
    this->setIsMortgaged(false);
}

PurchasableField::~PurchasableField() {

}

Player* PurchasableField::getOwner() {
    return this->owner;
}

void PurchasableField::setOwner(Player* owner) {
    this->owner = owner;
}

int PurchasableField::getPrice() {
    return this->price;
}

void PurchasableField::setPrice(int price) {
    this->price = price;
}


int PurchasableField::getRent() {
    return this->rent;
}

void PurchasableField::setRent(int rent) {
    this->rent = rent;
}

int PurchasableField::getMortgage() {
    return this->mortgage;
}

void PurchasableField::setMortgage(int mortgage) {
    this->mortgage = mortgage;
}

bool PurchasableField::isMortgaged() {
    return this->isUnderMortgage;
}

void PurchasableField::setIsMortgaged(bool isMortgaged) {
    this->isUnderMortgage = isMortgaged;
}

string PurchasableField::toString() {
    string fieldNumber = to_string(this->getFieldNumber());
    string fieldString = fieldNumber;

    if (this->getOwner()) {
        fieldString += " - Wlasciciel: " + this->getOwner()->getName();
    }
    else {
        fieldString += " - Wlasciciel: brak";
    }

    return fieldString;
}