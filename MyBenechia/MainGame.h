#pragma once
#include "Scene.h"
#include "HpColor.h"
#include "Floor.h"
#include "InputBox.h"
#include <string>

class TextBrickSpanwner;
class MainGame :
	public Scene
{
private:
	TextBrickSpanwner *textBrickSpanwer;
	Floor* floor;
	InputBox* inputBox;
	std::string inputStr;
	TCHAR scoreString[256];
	int score;
	int hp;
	HpColor color;
private:
	void UpdateCrash();
	void RenderMainGameObject(HDC hdc);
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

