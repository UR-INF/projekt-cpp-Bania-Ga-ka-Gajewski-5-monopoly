#include "player.hpp"

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {
    private:
        int board; // tu bedzie obiekt planszy
        Player players[];
    
    public:
        GameController();
        ~GameController();
        
};

#endif