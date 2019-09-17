#include "Tile.h"
#include "BitMap.h"
#include "Global.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
	Tile::m_collisionRECT = { m_pos.x, m_pos.y, m_pos.x + TILE1_SIZE, m_pos.y + TILE1_SIZE };
}

RECT Tile::GetCollisionRECT()
{
	return m_collisionRECT;
}

void Tile::Render()
{
	m_pBitmap->Render(m_pos.x + 20, m_pos.y + 20);
}