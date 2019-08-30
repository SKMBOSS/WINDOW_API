#pragma once
#include "Scene.h"
#include "TextBrick.h"
#include "HpColor.h"
#include <fstream>
#include "InputBox.h"
#include "Floor.h"
class Intro :
	public Scene
{
private:
	std::ifstream inFile;
	InputBox* inputBox;
	Floor* floor;
	RECT introTextBox = { 350,200,1050,700 };
	std::string inputStr;
	bool isTextEnd = false;
private:
	int introCycleColor = 6;
	int cycleColorchanger = -1;
private:
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

