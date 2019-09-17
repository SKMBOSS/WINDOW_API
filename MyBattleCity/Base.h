#pragma once
#include "Tile.h"
class Base :
	public Tile
{
public:
	virtual void SetPos(int x, int y);
	virtual void Render();
public:
	Base();
	Base(int x, int y);
	~Base();
};

