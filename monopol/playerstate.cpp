class PlayerState {
    private:
        int money;
        bool isInJail;
    
    PlayerState(int money, bool isInJail) {
        this->money = money;
        this->isInJail = isInJail;
    }

    ~PlayerState() {

    }

    public:
        bool getIsInJail() {
            return this->isInJail;
        }

        int getMoney() {
            return this->money;
        }
};