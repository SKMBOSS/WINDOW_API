#include "Metal.h"
#include "BitMap.h"
#include "ResourceManager.h"


Metal::Metal()
{
}

Metal::~Metal()
{
}

Metal::Metal(int x, int y)
{
	Tile::m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TILE_METAL);
	SetPos(x, y);
}

void Metal::SetPos(int x, int y)
{
	Tile::SetPos(x, y);
}

void Metal::Render()
{
	Tile::Render();
}
