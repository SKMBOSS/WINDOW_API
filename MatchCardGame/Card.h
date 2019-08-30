#pragma once
#include <Windows.h>

#define CARD_WIDTH		30;
#define CARD_HEIGHT		50;

class Card
{
public:
	int m_cardPosX;
	int m_cardPosY;
	HBITMAP hBitMap;
	HBITMAP hOLDBitMap;
public:
	void Init();
public:
	Card();
	~Card();
};

