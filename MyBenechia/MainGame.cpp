#include "MainGame.h"
#include "SceneManager.h"
#include "TextBrick.h"
#include "TextBrickSpawner.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	textBrickSpanwer = new TextBrickSpanwner("LEVEL01.txt");
	textBrickSpanwer->Init();
}
void MainGame::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_RETURN:
		if(textBrickSpanwer->IsCorrectAnswer(inputStr))
		{
			score += 100;
		}
		inputStr = "";
		break;
	case VK_BACK:
		inputStr.pop_back();
		break;
	default:
		inputStr += (TCHAR)wParam + 'a'-'A'; // ok
	}
}

void MainGame::Update()
{
	textBrickSpanwer->Update();
	UpdateCrash();
}
void MainGame::Render(HDC hdc)
{
	RenderMainGameObject(hdc);
	textBrickSpanwer->Render(hdc);
}
void MainGame::Release()
{
	delete textBrickSpanwer;
}

void MainGame::UpdateCrash()
{
	textBrickSpanwer->CrashBrickDelete(floor);
	textBrickSpanwer->CrashBrickDelete(inputBox);
}

void MainGame::RenderMainGameObject(HDC hdc)
{
	RenderFloor(hdc);
	RenderInpuBox(hdc);
	RenderScore(hdc);
}

void MainGame::RenderFloor(HDC hdc)
{
	Rectangle(hdc, floor.left, floor.top, floor.right, floor.bottom);
}
void MainGame::RenderInpuBox(HDC hdc)
{
	Rectangle(hdc, inputBox.left, inputBox.top, inputBox.right, inputBox.bottom);
	DrawText(hdc, inputStr.c_str(), -1, &inputBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void MainGame::RenderScore(HDC hdc)
{
	sprintf(scoreString, TEXT("score : %d"), score);
	TextOut(hdc, 1100, 50, scoreString, lstrlen(scoreString));
}