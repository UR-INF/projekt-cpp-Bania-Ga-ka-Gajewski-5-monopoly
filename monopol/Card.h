#pragma once
#include <string>

#ifndef CARD_H
#define CARD_H

using namespace std;

class Card
{
private:
	int cardId;
	string description;
public:
	Card(int cardId, string description);
	~Card();
	void setCardId(int cardId);
	int getCardId();
	void setDescription(string description);
	string getDescription();
};


#endif