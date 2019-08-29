#pragma once
#include "Scene.h"

class TextBrickSpanwner;
class MainGame :
	public Scene
{
private:
	RECT floor = { 2,700,1278,779 };
	RECT inputBox = { 570,600,710,701 };
	TextBrickSpanwner *textBrickSpanwer;
public:

public :
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	MainGame();
	~MainGame();
};

