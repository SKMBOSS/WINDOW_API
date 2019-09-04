#pragma once
#include "Scene.h"

class BitMap;
class Stage01 :
	public Scene
{
private:
	HWND			m_hWnd;
	BitMap* back;
	BitMap* back2;
	BitMap* player;
	int x;
	int y;
public:
	virtual void Init(HWND hWnd, HDC hdc);
	virtual void Input(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	Stage01();
	~Stage01();
};

