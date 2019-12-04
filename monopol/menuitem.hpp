#include <string>
#include "actiontype.hpp"

#ifndef MENUITEM_HPP
#define MENUITEM_HPP

using namespace std;

class MenuItem {
    private:
        string optionText;
        ActionType action;

    public:
        MenuItem(string optionText, ActionType action);
        ~MenuItem();
        void setOptionText(string optionText);
        string getOptionText();
        void setAction(ActionType action);
        ActionType getAction();

};

#endif