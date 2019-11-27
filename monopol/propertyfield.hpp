#include "field.hpp"
#include "player.hpp"
#include <string>

#ifndef PROPERTYFIELD_H
#define PROPERTYFIELD_H

using namespace std;

// Pole reprezentujace nieruchomosc
class PropertyField : public Field {
    private:
        Player* owner; // posiadacz własności
        string country;
        string city;
        int price;
        int pricing[6];
        int housingLevel; // poziom nieruchomosci (ile domkow, bedzie indexem dla pricing gdy zatrzyma się gracz-przeciwnik)
        int upgradeCost;
        int mortgage; // koszt zastawu hipotecznego
        bool isUnderMortgage; // czy pole jest zastawione
    
    public:
        PropertyField(Player* owner, string country, string city, int price, int pricing[], int housingLevel, int upgradeCost, int mortgage, bool isUnderMortgage, FieldType type, int fieldNumber);
        ~PropertyField();
        void setOwner(Player* owner);
        void upgrade(); // kup domek
        void degrade(); // sprzedaj domek
        int getCurrentRent(); // pobież wysokość aktualnego czynszu
        void setMortgage(bool mortgage);
};

#endif