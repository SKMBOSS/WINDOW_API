#pragma once
#include <Windows.h>

class Stage01;
class CircusGame
{
private:
	static CircusGame* m_sThis;
	Stage01* test;
public:
	static CircusGame* GetInstance();
public:
	void Init(HWND hWnd, HDC hdc);
	void Input(WPARAM wParam);
	void Update();
	void Draw(HDC hdc);
	void Release();

private:
	CircusGame();
public:
	~CircusGame();
};

