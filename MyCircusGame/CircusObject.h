#pragma once
#include <Windows.h>

class BitMap;
class CircusObject
{
protected:
	static int	m_sScreenPosX;
	static int	m_sScreenSpeed;
protected:
	void MoveScreenRight();
	void MoveScreenLeft();
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

