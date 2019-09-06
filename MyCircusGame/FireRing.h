#pragma once
#include "CircusObject.h"

enum FR_STATE
{
	FR_FRONT,
	FR_BACK
};

class FireRing :
	public CircusObject
{private:
	POINT		m_Pos;
	BitMap*		m_pBitMap;
	FR_STATE	m_eState;
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();

public:
	FireRing();
	~FireRing();
};

