#include "Card.h"

Card::Card() {}

Card::Card(int cardValue, Suit cardSuit)
{
	this->value = cardValue;
	this->suit = cardSuit;
}

Card::~Card() {}