#include "Card.h"

Card::Card(int cardId, string description){
	this->cardId = cardId;
	this->description = description;
}

Card::~Card() {
}

int Card::getCardId() {
	return this->cardId;
}

string Card::getDescription() {
	return this->description;
}

void Card::setCardId(int cardId) {
	this->cardId = cardId;
}

void Card::setDescription(string description) {
	this->description = description;
}

string Card::cardToString() {
	return std::to_string(this->cardId) +"|"+ this->description;
}
