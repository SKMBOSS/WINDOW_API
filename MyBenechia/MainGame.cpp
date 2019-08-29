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
	tbF = new TextBrickSpanwner("LEVEL01.txt");
	tbF->Init();
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
	tbF->Update();
}
void MainGame::Render(HDC hdc)
{
	tbF->Render(hdc);
}
void MainGame::Release()
{
	delete tbF;
}