#include "Base.h"
#include "BitMap.h"
#include "ResourceManager.h"

Base::Base()
{
}

Base::~Base()
{
}

Base::Base(int x, int y)
{
	Tile::m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TILE_BASE);
	SetPos(x, y);
}

void Base::SetPos(int x, int y)
{
	Tile::SetPos(x, y);
}

void Base::Render()
{
	Tile::Render();
}
