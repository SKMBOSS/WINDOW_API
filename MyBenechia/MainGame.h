#pragma once
#include "Scene.h"
#include "HpColor.h"
#include <string>

class TextBrickSpanwner;
class MainGame :
	public Scene
{
private:
	TextBrickSpanwner *textBrickSpanwer;
	RECT floor = { 2,700,1261,779 };
	RECT inputBox = { 570,600,710,701 };
	std::string inputStr;
	TCHAR scoreString[256];
	int score;
	int hp;
	HpColor color;
private:
	void UpdateCrash();
	void RenderMainGameObject(HDC hdc);
	void RenderFloor(HDC hdc);
	void RenderInpuBox(HDC hdc);
	void RenderScore(HDC hdc);
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	MainGame();
	~MainGame();
};

