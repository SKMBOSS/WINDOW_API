#pragma once
#include <string>
#include <Windows.h>
#include <time.h>
using namespace std;

class TextBrick
{
private:
	RECT rtPos;
	int speed;

	string targetText;
public:
	void Init();
	void Update();
	void Render(HDC _hdc);
	void Release();

	void SetPos();
	inline void SetSpeed(int _speed)
	{
		speed = _speed;
	}

	inline void DownBrick()
	{
		rtPos.top += speed;
		rtPos.bottom += speed;
	}
	bool isCrash();

	TextBrick();
	~TextBrick();
};

