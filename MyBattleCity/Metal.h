#pragma once
#include "Tile.h"

class Metal :
	public Tile
{
public:
	virtual void SetPos(int x, int y);
	virtual void Render(HDC hdc);
public:
	Metal();
	Metal(int x, int y);
	virtual ~Metal();
};

