#pragma once
#include "CircusObject.h"

enum BG_STATE
{
	BG_IDLE,
	BG_FRONT,
	BG_BACK
};

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
	int			m_speed;
	BG_STATE	m_eState;
	bool		m_bMove;

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

