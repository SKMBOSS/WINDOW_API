#pragma once
#include "Scene.h"
#include <vector>

enum STAGE01_STATE
{
	STAGE01_PLAYING,
	STAGE01_WATING,
	STAGE01_END
};

class BitMap;
class Stage01 :
	public Scene
{
private:
	HWND			m_hWnd;
	STAGE01_STATE	m_eState;

public:
	virtual void Init(HWND hWnd, HDC hdc);
	virtual void Update(float fElapseTime);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	Stage01();
	~Stage01();
};

