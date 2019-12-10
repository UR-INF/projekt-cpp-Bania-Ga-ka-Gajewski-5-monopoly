#include <string>
#include <vector>
#include "player.hpp"
#include "menu.hpp"
#include "board.hpp"
#include "field.hpp"

#ifndef RENDERER_HPP
#define RENDERER_HPP

using namespace std;

class Renderer {
    public:
        Renderer();
        ~Renderer();
        void renderPlayersInfo(vector<Player> playersToRender, Board* board);
        void renderPlayersMoveOrder(vector<Player> moveOrderToRender);
        void renderPlayerPositions(vector<Player> playersToRender);
        void renderCurrentPlayer(Player* playerToRender);
        void renderMessage(string message); 
        void renderMenu(Menu* menuToRender);
        void renderBoard(Board* boardToRender);
        void renderField(Field* fieldToRender);
        void restore_attributes();
};

#endif