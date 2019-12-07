#include "purchasablefield.hpp"
#include "player.hpp"
#include <string>

#ifndef RAILWAYFIELD_HPP
#define RAILWAYFIELD_HPP

using namespace std;

class RailwayField : public PurchasableField {
    private:
        string name;
    
    public:
        RailwayField(string name, Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber);
        ~RailwayField();
        string getName();
        void setName(string name);
        string toString();

};

#endif
