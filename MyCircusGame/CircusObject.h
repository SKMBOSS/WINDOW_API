#pragma once
#include <Windows.h>
#include <vector>

enum OBJECT_TAG
{
	TAG_OBJECT,
	TAG_ENEMY,
	TAG_WINFLOOR
};

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
	virtual OBJECT_TAG CollisionCheck(std::vector< CircusObject*>::iterator iter) { return TAG_OBJECT; }
	virtual RECT GetCollisonBox() { RECT temp; return temp; }
public:
	virtual void ReStart() {};
	virtual OBJECT_TAG GetTag() { return TAG_OBJECT; };
	virtual void Win(DWORD time) {};
	
public:
	CircusObject();
	virtual ~CircusObject();
};

