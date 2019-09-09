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
	BitMap*			m_pNumber[3];
	int				m_iMiter;

public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	void SetDigitNumberBitMap(int num, BitMap* arrBitMap[], int size);
	BitMap* GetNumberBitMap(int num);
public:
	Miter();
	~Miter();
};

