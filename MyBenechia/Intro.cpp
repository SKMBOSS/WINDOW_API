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

	inputBox = new InputBox();
	floor = new Floor();
	inputStr = "";
	isTextEnd = false;

	inputBox->Init();
	floor->Init();
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
	delete inputBox;
	delete floor;
	inFile.close();
}

void Intro::RenderIntroObject(HDC hdc)
{
	floor->Render(hdc,7);
	inputBox->Render(hdc, introCycleColor);
	RenderIntroText(hdc);
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