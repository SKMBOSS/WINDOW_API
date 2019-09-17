#include "Brick.h"
#include "BitMap.h"
#include "ResourceManager.h"

Brick::Brick()
{
}

Brick::~Brick()
{
}

Brick::Brick(int x, int y)
{
	Tile::m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TILE_BRICK);
	SetPos(x, y);
}

void Brick::SetPos(int x, int y)
{
	Tile::SetPos(x, y);
}

void Brick::Render()
{
	Tile::Render();
}

