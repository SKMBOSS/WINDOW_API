#pragma once
#include <Windows.h>
#include <list>
#include <string>
#include <fstream>

class TextBrick;
class TextBrickSpanwner
{
private:
	std::list<TextBrick*> tbBox;
	int cycleCount = 40;
	int maxCycle = 40;
	std::ifstream inFile;
	std::string fileName;
public:
	TextBrickSpanwner(std::string _fileName);
public:
	void CreateBricks();
	void DownBricks();
	int GetRandomPos();
	std::string GetNextWord();
	void CrashBrickDelete(RECT _floor, int &_hp);
	bool IsCorrectAnswer(std::string _inputStr);
public:
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
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	TextBrickSpanwner();
	~TextBrickSpanwner();
};

