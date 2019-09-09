#pragma once
#include "CircusObject.h"
#include <vector>

enum PLAYER_STATE
{
	PL_IDLE,
	PL_BACK,
	PL_FRONT,
	PL_JUMPUP,
	PL_JUMP_FRONT,
	PL_JUMP_BACK,
	PL_WIN,
	PL_DIE
};


class Player :
	public CircusObject
{
private:
	POINT			m_Pos;
	PLAYER_STATE	m_eState;
	BitMap*			m_pBitMap;
	DWORD			m_inputStartTime;
	int				m_speed;
	bool			m_bOnAnimator;
	int				m_iJumpConut;
	int				m_iMaxJumpCount;
	bool			m_bJump;
	bool			m_bWin;

public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	virtual OBJECT_TAG CollisionCheck(std::vector< CircusObject*>::iterator iter);
	virtual void ReStart();
	virtual void Win(DWORD time);
public:
	Player();
	~Player();
};

