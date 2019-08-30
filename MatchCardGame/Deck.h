#pragma once
#include "Card.h"
#include <vector>
class Deck
{
	std::vector<Card*> deck;
public :
	void init();
public:
	Deck();
	~Deck();
};

