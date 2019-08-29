#include "TextBrick.h"

TextBrick::TextBrick()
{
}

TextBrick::~TextBrick()
{
}

TextBrick::TextBrick(int rtPos, int _speed, string _targetText)
{
	SetSpeed(_speed);
	targetText = _targetText;
	SetRtCollider(rtPos);
}

void TextBrick::SetRtCollider(int rtPos)
{
	int spaceArea = targetText.length();

	rtCollider.left = rtPos - spaceArea*5;
	rtCollider.top = 0;
	rtCollider.right = rtPos + spaceArea * 5;
	rtCollider.bottom = 35;
}

void TextBrick::Update()
{
	DownBrick();
}

void TextBrick::Render(HDC _hdc)
{
	Rectangle(_hdc, rtCollider.left, rtCollider.top, rtCollider.right, rtCollider.bottom);
	DrawText(_hdc, targetText.c_str(), -1, &rtCollider, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}