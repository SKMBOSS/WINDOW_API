#pragma once
#include "CircusObject.h"

enum PLAYER_STATE
{
	PL_IDLE,
	PL_BACK,
	PL_FRONT,
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
	bool			m_bMove;
	bool			m_bOnAnimator;

private:
	bool DelayEnd(DWORD time);
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	Player();
	~Player();
};

