#pragma once
#include <Windows.h>
class MyBenechia
{
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	MyBenechia();
	~MyBenechia();
};

