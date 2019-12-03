#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerState {
    private:
        int money;
        bool isInJail;  
        bool bankrupt;
		int outOfJailCards;

    public:
        PlayerState(int money, bool isInJail, bool bankrupt, int outOfJailCards);

        ~PlayerState();

        bool getIsInJail();

        int getMoney();

        void setMoney(int money);

        void setIsInJail(bool isInJail);

        bool isBankrupt();

        void setBankrupt(bool bankrupt);

		int getOutOfJailCards();

		void setOutOfJailCards(int numcard);
};

#endif