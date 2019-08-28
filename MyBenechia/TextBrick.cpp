#include "TextBrick.h"

TextBrick::TextBrick()
{
}

TextBrick::~TextBrick()
{
}

void TextBrick::Init()
{
	srand(time(nullptr));
	SetPos();
	SetSpeed(10);
}

void TextBrick::SetPos()
{
	rtPos.left = rand() % 539 +1;
	rtPos.top = 10;
	rtPos.right = rtPos.left + 100;
	rtPos.bottom = 50;
}

void TextBrick::Update()
{
	DownBrick();
}

void TextBrick::Render(HDC _hdc)
{
	Rectangle(_hdc, rtPos.left, rtPos.top, rtPos.right, rtPos.bottom);
	//Rectangle(_hdc, 100,100,200,200);
}