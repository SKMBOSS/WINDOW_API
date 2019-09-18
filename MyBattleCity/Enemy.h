#pragma once
#include <Windows.h>
#include <list>

using namespace std;

enum ETANK_STATE
{
	ETANK_IDLE,
	ETANK_UP,
	ETANK_DOWN,
	ETANK_LEFT,
	ETANK_RIGHT,
};

enum EBULLET_STATE
{
	EBULLET_UP,
	EBULLET_DOWN,
	EBULLET_LEFT,
	EBULLET_RIGHT,
};

class BitMap;
class Tile;
class Enemy
{
private:
	BitMap*		  m_pBitmap;
	float		  m_posX;
	float		  m_posY;
	RECT		  m_collisionRECT;
	ETANK_STATE	  m_eState;
	DWORD		  m_startInputTime;
	list<Tile*>*  m_listTile;
	int			  m_iSavedKey;

	BitMap*		  m_pBulletBitMap;
	EBULLET_STATE  m_eBUlletState;
	EBULLET_STATE  m_eBUlletState2;
	float		  m_BulletPosX;
	float		  m_BulletPosY;
	bool		  m_BulletGoing;
	RECT		  m_BulletCollisionRECT;
	void		  BulletInput();
	void		  UpdateBullet(float fElapseTime);
	void		  BulletCollisionCheck();

	BitMap*		  m_pBulletEffectBitMap;
	float		  m_BulletEffectPosX;
	float		  m_BulletEffectPosY;
	bool		  m_BulletEffectOn;
	DWORD		  m_startEffectTime;

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
	Enemy();
	Enemy(list<Tile*>* listTile);
	~Enemy();
};

