#pragma once
#include <Windows.h>
#include "HpColor.h"
class Floor
{
private:
	RECT floor;
	HpColor color;
public:
	inline RECT GetRect()
	{
		return floor;
	}
public:
	void Init();
	void Render(HDC hdc, int color);
public:
	Floor();
	~Floor();
};

