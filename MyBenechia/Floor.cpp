#include "Floor.h"

Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::Init()
{
	floor = { 2,700,1261,779 };
}

void  Floor::Render(HDC hdc, int idx)
{
	HBRUSH newBrush, oldBrush;

	newBrush = CreateSolidBrush(RGB(color._RGB[idx].R, color._RGB[idx].G, color._RGB[idx].B));
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, floor.left, floor.top, floor.right, floor.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);
}