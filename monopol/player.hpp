#ifndef Player_h
#define Player_h

#include "playerstate.hpp";
#include <string>;

using namespace std;

class Player {
    private:
        string name;
        PlayerState playerState;
        int position;
    
    public:
        Player(string name, PlayerState playerState, int position);
        ~Player();

        string getName();
        void setName(string name);
        int getPosition();
        void setPosition(int position);
        bool isInJail();
        bool isSolvent(int rent);

};

#endif