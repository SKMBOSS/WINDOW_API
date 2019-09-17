#pragma once
#include <Windows.h>
#include <list>

using namespace std;

enum TANK_STATE
{
	TANK_IDLE,
	TANK_UP,
	TANK_DOWN,
	TANK_LEFT,
	TANK_RIGHT,
};

class BitMap;
class TileMap;
class Player
{
private:
	BitMap*		 m_pBitmap;
	float		 m_posX;
	float		 m_posY;
	RECT		 m_collisionRECT;
	TANK_STATE	 m_eState;
	DWORD		 m_startInputTime;
	TileMap*     m_pTileMap;
	
public:
	void SetStartInfo();
	void UpdatePos(float fElapseTime);
	void UpdateBitMap();
	void OperateInput();
	bool CollisionCheck();
public:
	void Init(TileMap* pTileMap);
	void Update(float fElapseTime);
	void Render();
	void Release();
public:
	Player();
	~Player();
};

