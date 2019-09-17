#pragma once
#include <Windows.h>

enum TANK_STATE
{
	TANK_IDLE,
	TANK_UP,
	TANK_DOWN,
	TANK_LEFT,
	TANK_RIGHT,
};

class BitMap;
class Player
{
private:
	BitMap*		 m_pBitmap;
	POINT		 m_pos;
	RECT		 m_collisionRECT;
	TANK_STATE	 m_eState;
	DWORD		 m_startInputTime;
	
public:
	void SetStartInfo();
	void UpdatePos(float fElapseTime);
	void UpdateBitMap();
	void OperateInput();
public:
	void Init();
	void Update(float fElapseTime);
	void Render();
	void Release();
public:
	Player();
	~Player();
};

