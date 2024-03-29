#pragma once
#include <Windows.h>
#include "HpColor.h"
class InputBox 
{
private:
	RECT inputBox;
	HpColor color;
public:
	inline RECT GetRect()
	{
		return inputBox;
	}
public :
	void Init();
	void Render(HDC hdc, int color);
public:
	InputBox();
	~InputBox();
};

