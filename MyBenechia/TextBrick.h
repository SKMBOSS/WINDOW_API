#pragma once
#include <string>
#include <Windows.h>
#include <time.h>
using namespace std;

class TextBrick
{
private:
	int textPosX;
	int textPosY = 0;
	RECT rtCollider;
	int speed;
	string targetText;
public:
	TextBrick(int _textPosX, int _speed, string _targetText);
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC _hdc);
	void Release();
public:
	void SetRtCollider();
	inline void SetSpeed(int _speed)
	{
		speed = _speed;
	}
	inline void DownBrick()
	{
		textPosY += speed;
		rtCollider.bottom += speed;
		rtCollider.top += speed;
	}
	bool isCrash();

	TextBrick();
	~TextBrick();
};

