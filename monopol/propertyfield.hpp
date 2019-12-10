#include "purchasablefield.hpp"
#include "player.hpp"
#include <string>

#ifndef PROPERTYFIELD_H
#define PROPERTYFIELD_H

using namespace std;

// Pole reprezentujace nieruchomosc
class PropertyField : public PurchasableField {
    private:
        string country;
        string city;
        int pricing[6];
        int housingLevel; // poziom nieruchomosci (ile domkow, bedzie indexem dla pricing gdy zatrzyma się gracz-przeciwnik)
        int upgradeCost;
    
    public:
        PropertyField(string country, string city, int pricing[], int housingLevel, int upgradeCost, Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber);
        ~PropertyField();
        void upgrade(); // kup domek
        void degrade(); // sprzedaj domek
        int getRent(); // pobież wysokość aktualnego czynszu
        int getHousingLevel();
        string getPropertyInfo();
        string toString();
        string getCountryName();
        string getShortName();
        int getUpgradeCost();
};

#endif