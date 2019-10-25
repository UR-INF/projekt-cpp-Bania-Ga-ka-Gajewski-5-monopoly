class PlayerState {
    private:
        int money;
        bool isInJail;  

    public:
        PlayerState(int money, bool isInJail) {
            this->setMoney(money);
            this->setIsInJail(isInJail);
        }

        ~PlayerState() {

        }

        bool getIsInJail() {
            return this->isInJail;
        }

        int getMoney() {
            return this->money;
        }

        void setMoney(int money) {
            this->money = money;
        }

        void setIsInJail(bool isInJail) {
            this->isInJail = isInJail;
        }
};