#pragma once
#include "CircusObject.h"

class BackGround :
	public CircusObject
{
private:
	POINT		m_topPos;
	POINT		m_bottomPos;
	BitMap*		m_pTopBitMap;
	BitMap*		m_pBottomBitMap;
	int			m_iThisNum;


	static int  m_sBackGroundNumber;
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

