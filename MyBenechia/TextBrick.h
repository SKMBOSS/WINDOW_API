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
public:
	TextBrick(int rtPos, int _speed, string _targetText);
public:
	inline void SetSpeed(int _speed)
	{
		speed = _speed;
	}
	inline RECT GetRtCollider()
	{
		return rtCollider;
	}
	inline std::string GetTargetText()
	{
		return targetText;
	}
private:
	void SetRtCollider(int rtPos);
	inline void DownBrick()
	{
		rtCollider.bottom += speed;
		rtCollider.top += speed;
	}
	void RenderBrick(HDC hdc);
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	TextBrick();
	~TextBrick();
};

