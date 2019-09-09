#pragma once
#include "CircusObject.h"

class ScoreBoard :
	public CircusObject
{
private:
	POINT		m_Pos;
	BitMap*		m_pBitMap;
	//현재스코어
	int			m_iScore;
	BitMap*		m_pScore[6];
	//보너스
	int			m_iBonus;
	DWORD		m_BonusTime;
	BitMap*		m_pBonus[4];
	
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();

public:
	ScoreBoard();
	~ScoreBoard();
};

