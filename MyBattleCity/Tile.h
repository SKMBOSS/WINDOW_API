#pragma once
#include <Windows.h>

enum TILE_TYPE
{
	BRICK,
	METAL
};

class BitMap;
class Tile
{
protected:
	BitMap* m_pBitmap;
	POINT	m_pos;
	RECT	m_collisionRECT;
public:
	virtual void SetPos(int x, int y);
	virtual RECT GetCollisionRECT();
public:
	virtual void Render();
public:
	Tile();
	virtual ~Tile();
};

