#pragma once
#include "CircusObject.h"
class WinFloor :
	public CircusObject
{
private:
	POINT		m_Pos;
	BitMap*		m_pBitMap;
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	virtual RECT GetCollisonBox();
	inline virtual OBJECT_TAG GetTag()
	{
		return TAG_WINFLOOR;
	}
public:
	WinFloor();
	~WinFloor();
};
