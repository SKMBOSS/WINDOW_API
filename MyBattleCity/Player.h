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

enum BULLET_STATE
{
	BULLET_UP,
	BULLET_DOWN,
	BULLET_LEFT,
	BULLET_RIGHT,
};

class BitMap;
class Tile;
class Player
{
private:
	BitMap*		  m_pBitmap;
	float		  m_posX;
	float		  m_posY;
	RECT		  m_collisionRECT;
	TANK_STATE	  m_eState;
	DWORD		  m_startInputTime;
	list<Tile*>*  m_listTile;


	BitMap*		  m_pBulletBitMap;
	BULLET_STATE  m_eBUlletState;
	float		  m_BulletPosX;
	float		  m_BulletPosY;
	bool		  m_BulletGoing;
	RECT		  m_BulletCollisionRECT;

	void		  UpdateBullet(float fElapseTime);
public:
	void SetStartInfo();
	void UpdatePos(float fElapseTime);
	void UpdateBitMap();
	void OperateInput();
	bool CollisionCheck();
public:
	void Init();
	void Update(float fElapseTime);
	void Render();
	void Release();
public:
	Player();
	Player(list<Tile*>* listTile);
	~Player();
};

