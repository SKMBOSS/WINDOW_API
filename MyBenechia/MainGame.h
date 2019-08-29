#pragma once
#include "Scene.h"

class TextBrickSpanwner;
class MainGame :
	public Scene
{
private:
	RECT rt = { 50,50,200,300 };
	TextBrickSpanwner *tbF;
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

