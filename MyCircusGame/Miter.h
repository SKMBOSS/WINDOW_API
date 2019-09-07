#pragma once
#include "CircusObject.h"

enum MITER_STATE
{
	MITER_IDLE,
	MITER_BACK,
	MITER_FRONT,
};

class Miter :
	public CircusObject
{
private:
	POINT			m_Pos;
	MITER_STATE		m_eState;
	BitMap*			m_pBitMap;
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	Miter();
	~Miter();
};

