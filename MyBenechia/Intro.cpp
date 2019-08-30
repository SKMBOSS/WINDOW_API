#include "Intro.h"
#include "SceneManager.h"

Intro::Intro()
{
}

Intro::~Intro()
{
}

void Intro::Init()
{
	inFile.open("IntroText.txt");
}
void Intro::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_RETURN:
		if (!isTextEnd)
		{
			LoadText(inFile);
		}
		else
		SceneManager::GetInstance()->ChangeScene(SCENE_STATE::MAIN_GAME);
	}
}

void Intro::Update()
{
	if (ResetCycleCount())
	{
		ChangeCycleColor();
	}
	ReduceCycleCount();
}
void Intro::Render(HDC hdc)
{
	RenderIntroObject(hdc);
}

void Intro::Release()
{
}

void Intro::RenderIntroObject(HDC hdc)
{
	RenderFloor(hdc);
	RenderInpuBox(hdc);
	RenderIntroText(hdc);
}

void Intro::RenderFloor(HDC hdc)
{
	HBRUSH newBrush, oldBrush;

	newBrush = CreateSolidBrush(RGB(color._RGB[7].R, color._RGB[7].G, color._RGB[7].B));
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, floor.left, floor.top, floor.right, floor.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);
}

void Intro::RenderInpuBox(HDC hdc)
{
	HBRUSH newBrush, oldBrush;

	newBrush = CreateSolidBrush(RGB(color._RGB[introCycleColor].R, color._RGB[introCycleColor].G, color._RGB[introCycleColor].B));
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, inputBox.left, inputBox.top, inputBox.right, inputBox.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);
}

void Intro::RenderIntroText(HDC hdc)
{
	DrawText(hdc, inputStr.c_str(), -1, &introTextBox, DT_CENTER);
}

void Intro::ChangeCycleColor()
{
	if (introCycleColor == 0)
		introCycleColor = 7;

	introCycleColor--; 
}

void Intro::LoadText(std::ifstream& _inFile)
{
	char szBuf[256];
	_inFile.getline(szBuf, 100);

	inputStr += szBuf;
	inputStr += '\n';

	if (_inFile.eof())
		isTextEnd = true;
}