#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerState {
    private:
        int money;
        bool isInJail;  

    public:
        PlayerState(int money, bool isInJail);

        ~PlayerState();

        bool getIsInJail();

        int getMoney();

        void setMoney(int money);

        void setIsInJail(bool isInJail);
};

#endif