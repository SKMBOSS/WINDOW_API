#pragma once
#include <Windows.h>
#include <list>

class Tile;
class TileMap
{
private :
	enum TILE_TYPE_FOR_LOAD
	{
		TILE_DEFAULT,

		TILE_BRICK_FULL,
		TILE_BRICK_TOP,
		TILE_BRICK_BOT,
		TILE_BRICK_LEFT,
		TILE_BRICK_RIGHT,

		TILE_METAL_FULL,
		TILE_METAL_TOP,
		TILE_METAL_BOT,
		TILE_METAL_LEFT,
		TILE_METAL_RIGHT,

		TILE_ICE,
		TILE_FOREST,
		TILE_WATER,

		TILE_BRICK_BOT_LEFT,
		TILE_BRICK_BOT_RIGHT,

		TILE_LIFE
	};
private:
	std::list<Tile*> m_listTile;
private:
	void LoadTile();
public:
	inline std::list<Tile*> GetListTile()
	{
		return m_listTile;
	}
public :
	void Init();
	void Render();
	void Release();
public:
	TileMap();
	~TileMap();
};

