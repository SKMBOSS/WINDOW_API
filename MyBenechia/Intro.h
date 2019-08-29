#pragma once
#include "Scene.h"
#include "TextBrick.h"

class Intro :
	public Scene
{
private:
	RECT rt = { 50,0,100,50 };
	TextBrick *tb;
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	Intro();
	~Intro();
};

