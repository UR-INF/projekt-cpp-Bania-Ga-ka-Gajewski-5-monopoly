#include "menuitem.hpp"
#include "actiontype.hpp"

MenuItem::MenuItem(string optionText, ActionType action) {
    this->setOptionText(optionText);
    this->setAction(action);
}

MenuItem::~MenuItem() {}

void MenuItem::setOptionText(string optionText) {
    this->optionText = optionText;
}

void MenuItem::setAction(ActionType action) {
    this->action = action;
}

string MenuItem::getOptionText() {
    return this->optionText;
}

ActionType MenuItem::getAction() {
    return this->action;
}