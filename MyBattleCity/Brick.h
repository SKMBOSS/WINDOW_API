#pragma once
#include "Tile.h"

class Brick :
	public Tile
{
public:
	virtual void SetPos(int x, int y);
	virtual void Render(HDC hdc);
public:
	Brick();
	Brick(int x, int y);
	virtual ~Brick();
};

