#pragma once
#include "CircusObject.h"

class BackGround :
	public CircusObject
{
private:
	static int  m_sBackGroundNumber;
private:
	BitMap*		m_pTopBitMap;
	BitMap*		m_pBottomBitMap;
	int			m_iBackPosX;
	int			m_iTopBackPosY;
	int			m_iBottomBackPosY;
	int			m_iThisNum;
private:
	int			GetThisBackGroundSizeX();
	int			GetWholeBackGroundSizeX();
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	BackGround();
	virtual ~BackGround();
};

