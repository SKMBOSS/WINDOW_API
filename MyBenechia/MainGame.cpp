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
	floor = new Floor();
	inputBox = new InputBox();
	score = 0;
	hp = 6;

	textBrickSpanwer->Init();
	floor->Init();
	inputBox->Init();
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
	delete floor;
	delete inputBox;
}

void MainGame::UpdateCrash()
{
	textBrickSpanwer->CrashBrickDelete(floor->GetRect(),hp);
	textBrickSpanwer->CrashBrickDelete(inputBox->GetRect(),hp);
}

void MainGame::RenderMainGameObject(HDC hdc)
{
	floor->Render(hdc, 7);
	inputBox->Render(hdc,hp);
	RenderScore(hdc);
}

void MainGame::RenderScore(HDC hdc)
{
	sprintf(scoreString, TEXT("score : %d"), score);
	TextOut(hdc, 1100, 50, scoreString, lstrlen(scoreString));
}