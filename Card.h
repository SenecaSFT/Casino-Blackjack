#pragma once

enum Suit
{
	SPADE,
	HEART,
	DIAMOND,
	CLUB
};

enum PlayState
{
	BLACKJACK,
	BUST,
	VALID
};

enum GameState
{
	PL_WIN,
	PL_LOSS,
	DRAW

};

class Card
{
public:
	int value;
	Suit suit;
	
	Card(int cardValue, Suit cardSuit);
	Card();

	~Card();
};