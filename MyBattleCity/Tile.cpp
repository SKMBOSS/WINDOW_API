#include "Tile.h"
#include "BitMap.h"

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
}

void Tile::Render(HDC hdc)
{
	m_pBitmap->Render(hdc, m_pos.x +20, m_pos.y +20);
}
