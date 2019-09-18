#pragma once
#include "Scene.h"
#include <list>
#include <vector>

using namespace std;

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

class Tile;
class BitMap;
class Player;
class Enemy;
class Stage :
	public Scene
{
private:
	list<Tile*>		m_listTile;
	BitMap*			m_BackGround;
	BitMap*			m_mapBackGround;
	Player*			m_pPlayer;
	Enemy*			m_pEnemy;

public:
	void LoadTile();
public:
	virtual void Init();
	virtual void Update(float fElapseTime);
	virtual void Render();
	virtual void Release();

public:
	Stage();
	~Stage();
};

