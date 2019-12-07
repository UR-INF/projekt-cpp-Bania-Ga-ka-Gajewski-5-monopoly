#include "field.hpp"
#include "player.hpp"
#include <string>

#ifndef PURCHASABLEFIELD_HPP
#define PURCHASABLEFIELD_HPP

using namespace std;

class PurchasableField : public Field {
    private:
        Player* owner;
        int price;
        int rent;
        int mortgage;
        bool isUnderMortgage;
    
    public:
        PurchasableField(Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber);
        ~PurchasableField();
        Player* getOwner();
        void setOwner(Player* owner);

        int getPrice();
        void setPrice(int price);
        
        virtual int getRent();
        void setRent(int rent);

        int getMortgage();
        void setMortgage(int mortgage);
        
        bool isMortgaged();
        void setIsMortgaged(bool isMortgaged);
        
        string toString();

};

#endif