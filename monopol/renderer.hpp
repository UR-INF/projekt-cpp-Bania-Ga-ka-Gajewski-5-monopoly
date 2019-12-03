#include <string>
#include <vector>
#include "player.hpp"

#ifndef RENDERER_HPP
#define RENDERER_HPP

using namespace std;

class Renderer {
    public:
        Renderer();
        ~Renderer();
        void renderPlayersMoveOrder(vector<Player> moveOrderToRender);
        void renderPlayerPositions(vector<Player> playersToRender);
        void renderCurrentPlayer(Player* playerToRender);
        void renderMessage(string message); 
};

#endif