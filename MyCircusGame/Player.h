#pragma once
#include "CircusObject.h"

enum PLAYER_STATE
{
	WAIT,
	BACK,
	FRONT,
	WIN,
	DIE
};

class Player :
	public CircusObject
{
private:
	PLAYER_STATE	m_eState;
	DWORD			m_inputStartTime;
	bool			m_bMove;
private:
	void SetStateBitMap();
	void DelaySetBitMap(int time);
	void SetInputStartTime();
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

