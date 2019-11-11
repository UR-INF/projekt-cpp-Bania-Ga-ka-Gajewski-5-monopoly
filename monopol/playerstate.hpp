#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerState {
    private:
        int money;
        bool isInJail;  
        bool bankrupt;

    public:
        PlayerState(int money, bool isInJail, bool bankrupt);

        ~PlayerState();

        bool getIsInJail();

        int getMoney();

        void setMoney(int money);

        void setIsInJail(bool isInJail);

        bool isBankrupt();

        void setBankrupt(bool bankrupt);
};

#endif