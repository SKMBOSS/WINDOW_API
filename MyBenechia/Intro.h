#pragma once
#include "Scene.h"
#include "TextBrick.h"
#include "HpColor.h"
#include <fstream>

class Intro :
	public Scene
{
private:
	RECT floor = { 2,700,1261,779 };
	RECT inputBox = { 570,600,710,701 };
	RECT introTextBox = { 350,200,1050,700 };
	std::ifstream inFile;
	std::string inputStr;
	bool isTextEnd = false;
	HpColor color;
	int introCycleColor = 6;
	int cycleColorchanger = -1;
	int cycleCount = 40;
	int maxCycle = 40;
private:
	inline void ReduceCycleCount()
	{
		cycleCount--;
	}
	inline bool ResetCycleCount()
	{
		if (cycleCount == 0)
		{
			cycleCount = maxCycle;
			return true;
		}

		else
			return false;
	}
	void RenderIntroObject(HDC hdc);
	void RenderFloor(HDC hdc);
	void RenderInpuBox(HDC hdc);
	void RenderIntroText(HDC hdc);
	void ChangeCycleColor();
	void LoadText(std::ifstream& _inFile);
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

