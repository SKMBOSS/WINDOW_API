#pragma once
#include <Windows.h>

class BitMap;
class CircusObject
{
protected:
	POINT		m_Pos;
protected:
	void SetObjectPos(int x, int y);
public:
	virtual void Init() = 0;
	virtual void Input(WPARAM wParam) = 0;
	virtual void TerminateInput(WPARAM wParam) = 0;
	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Release() = 0;
public:
	CircusObject();
	virtual ~CircusObject();
};

