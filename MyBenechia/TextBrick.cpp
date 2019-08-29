#include "TextBrick.h"

TextBrick::TextBrick()
{
}

TextBrick::~TextBrick()
{
}

TextBrick::TextBrick(int _textPosX, int _speed, string _targetText)
{
	textPosX = _textPosX;
	SetSpeed(_speed);
	targetText = _targetText;
	SetRtCollider();
}

void TextBrick::SetRtCollider()
{
	int spaceArea = targetText.length();

	rtCollider.left = textPosX - 5;
	rtCollider.top = textPosY - 2;
	rtCollider.right = textPosX + spaceArea/2 * 15 +10;
	rtCollider.bottom = textPosY + 20;
}

void TextBrick::Update()
{
	DownBrick();
}

void TextBrick::Render(HDC _hdc)
{
	Rectangle(_hdc, rtCollider.left, rtCollider.top, rtCollider.right, rtCollider.bottom);
	TextOut(_hdc, textPosX, textPosY, targetText.c_str(), targetText.length());
}