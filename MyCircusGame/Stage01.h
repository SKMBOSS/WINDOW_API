#pragma once
#include "Scene.h"
#include <vector>

enum STAGE01_STATE
{
	STAGE01_PLAYING,
	STAGE01_WATING,
	STAGE01_END
};

class BitMap;
class CircusObject;
class Stage01 :
	public Scene
{
private:
	HWND									m_hWnd;
	DWORD									m_DeathTime;
	STAGE01_STATE							m_eState;
	BitMap*									m_pScreenBitMap;
	bool									m_bWaiting;
	std::vector< CircusObject*>				m_vecObj;
	std::vector< CircusObject*>::iterator   m_FireStartIter;
	std::vector< CircusObject*>::iterator   m_WinFloorIter;
	std::vector< CircusObject*>::iterator	m_PlayerIter;
	std::vector< CircusObject*>::iterator	m_ScoreBoardIter;
	
public:
	void CircusObjectMake();
	void CollisionCheckForState();
	void CollisionCheckForScore();
public:
	virtual void Init(HWND hWnd, HDC hdc);
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();

public:
	Stage01();
	~Stage01();
};

