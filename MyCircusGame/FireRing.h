#pragma once
#include "CircusObject.h"

class FireRing :
	public CircusObject
{private:
	static int	m_sFireRingNumber;
	int			miThisNumber;
	POINT		m_Pos;
	BitMap*		m_pBitMap;
	bool		m_bIsOnScreen;
	DWORD		m_inputStartTime;
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
	virtual RECT GetCollisonBox();
	virtual void ReStart();

public:
	FireRing();
	~FireRing();
};

