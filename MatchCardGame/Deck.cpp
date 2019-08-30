#include "Deck.h"



Deck::Deck()
{
}


Deck::~Deck()
{
}

void Deck::init()
{
	for (int i = 0; i < 11; i++)
	{
		Card *c = new Card;
		c->m_cardPosX = i * CARD_WIDTH;
		c->m_cardPosY = i * CARD_HEIGHT;

		deck.push_back(c);
	}
}