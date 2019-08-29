#pragma once
#include <string>
#include <Windows.h>
#include <time.h>
using namespace std;

class TextBrick
{
private:
	RECT rtCollider;
	int speed;
	string targetText;
	bool isCrash = false;
public:
	TextBrick(int rtPos, int _speed, string _targetText);
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC _hdc);
	void Release();
public:
	void SetRtCollider(int rtPos);
	inline void SetSpeed(int _speed)
	{
		speed = _speed;
	}
	inline void DownBrick()
	{
		rtCollider.bottom += speed;
		rtCollider.top += speed;
	}
	inline void SetIsCrash()
	{
		isCrash = true;
	}
	inline bool GetIsCrash()
	{
		return isCrash;
	}
	inline RECT GetRtCollider()
	{
		return rtCollider;
	}
	TextBrick();
	~TextBrick();
};

