#pragma once
#include <Windows.h>

class Stage01;
class CircusGame
{
private:
	static CircusGame* m_sThis;
	
public:
	static CircusGame* GetInstance();
public:
	void Init(HWND hWnd, HDC hdc);
	void Input(WPARAM wParam);
	void TerminateInput(WPARAM wParam);
	void Update();
	void Draw(HDC hdc);
	void Release();

private:
	CircusGame();
public:
	~CircusGame();
};

