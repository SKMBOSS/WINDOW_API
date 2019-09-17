#pragma once
#include <Windows.h>

class BitMap;
class Tile
{
protected:
	BitMap* m_pBitmap;
	POINT	m_pos;
public:
	virtual void SetPos(int x, int y);
	virtual void Render();
public:
	Tile();
	virtual ~Tile();
};

