#include "purchasablefield.hpp"
#include <string>

#ifndef RENTMULTIPIERFIELD_HPP
#define RENTMULTIPIERFIELD_HPP

using namespace std;

class RentMultipierField : public PurchasableField {
    private:
        string name;
    public:
        RentMultipierField(string name, Player* owner, int price, int rent, int mortgage, FieldType type, int fieldNumber);
        ~RentMultipierField();
        string getName();
        void setName(string name);
        int getRent() override;
        string toString();
};

#endif