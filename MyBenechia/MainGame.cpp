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
		SceneManager::GetInstance()->ChangeScene(SCENE_STATE::INTRO);
	}
}
void MainGame::Update()
{
	textBrickSpanwer->Update();
	textBrickSpanwer->CrashBrickDelete(floor);
	textBrickSpanwer->CrashBrickDelete(inputBox);
}
void MainGame::Render(HDC hdc)
{
	Rectangle(hdc, floor.left, floor.top, floor.right, floor.bottom);
	Rectangle(hdc, inputBox.left, inputBox.top, inputBox.right, inputBox.bottom);
	textBrickSpanwer->Render(hdc);
}
void MainGame::Release()
{
	delete textBrickSpanwer;
}