#include "InputBox.h"

InputBox::InputBox()
{
}

InputBox::~InputBox()
{
}

void InputBox::Init()
{
	inputBox = { 570,600,710,701 };
}

void  InputBox::Render(HDC hdc, int idx)
{
	HBRUSH newBrush, oldBrush;

	newBrush = CreateSolidBrush(RGB(color._RGB[idx].R, color._RGB[idx].G,color._RGB[idx].B));
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, inputBox.left, inputBox.top, inputBox.right, inputBox.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);
}