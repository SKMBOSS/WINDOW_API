#pragma once
#include <Windows.h>
#include <vector>

class BitMap;
class CircusObject
{
protected:
	static int	m_sScreenPosX;
	static int	m_sSavedPosX;
	static int	m_sScreenSpeed;
protected:
	void MoveScreenRight();
	void MoveScreenLeft();
	int	 GetDirection();
public:
	virtual void Init() = 0;
	virtual void Input(WPARAM wParam) = 0;
	virtual void TerminateInput(WPARAM wParam) = 0;
	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Release() = 0;
public:
	virtual bool CollisionCheck(std::vector< CircusObject*>::iterator iter) { return false; }
	virtual RECT GetCollisonBox() { RECT temp; return temp; }
public:
	virtual void ReStart() {};
	
public:
	CircusObject();
	virtual ~CircusObject();
};

