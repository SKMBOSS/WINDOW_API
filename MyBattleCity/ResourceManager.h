#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_BG_GAME,
	RES_BG_MAP,
	//tile(16 *16)
	RES_TILE_BRICK,
	RES_TILE_METAL,
	RES_TILE_ICE,
	RES_TILE_BUSH,
	RES_TILE_WATER,
	RES_TILE_BASE,
	RES_TILE_BASE_BROKEN,

	RES_TANK_PLAYER1_UP_00,
	RES_TANK_PLAYER1_UP_01,
	RES_TANK_PLAYER1_DOWN_00,
	RES_TANK_PLAYER1_DOWN_01,
	RES_TANK_PLAYER1_LEFT_00,
	RES_TANK_PLAYER1_LEFT_01,
	RES_TANK_PLAYER1_RIGHT_00,
	RES_TANK_PLAYER1_RIGHT_01,

	RES_BULLET_UP,
	RES_BULLET_DOWN,
	RES_BULLET_LEFT,
	RES_BULLET_RIGHT,

	RES_TYPE_END
};

class BitMap;
class ResourceManager
{
private:
	static ResourceManager* m_sThis;
	BitMap* m_pBitMap[RES_TYPE_END];
	vector<string> resPath;
public:
	static ResourceManager* GetInstance();
	BitMap* GetBitMap(int index);
	SIZE GetBitMapSize(int index);
private:
	void InitResPath();
	void InitBitMap(HDC hdc);
public:
	void Init(HDC hdc);
	void Release();
private:
	ResourceManager();
public:
	~ResourceManager();
};

