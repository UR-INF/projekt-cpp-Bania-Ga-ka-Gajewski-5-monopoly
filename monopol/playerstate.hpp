#ifndef PlayerState_h
#define PlayerState_h

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