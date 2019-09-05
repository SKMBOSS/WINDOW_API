#pragma once
#include "Scene.h"
#include <vector>

class BitMap;
class CircusObject;
class Stage01 :
	public Scene
{
private:
	HWND							m_hWnd;
	std::vector< CircusObject*>		m_vecObj;
	
public:
	virtual void Init(HWND hWnd, HDC hdc);
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	Stage01();
	~Stage01();
};

