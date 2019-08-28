#include "MainGame.h"
#include "SceneManager.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	tb = new TextBrick();
	tb->Init();
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
	tb->Update();
}
void MainGame::Render(HDC hdc)
{
	tb->Render(hdc);
}
void MainGame::Release()
{
	delete tb;
}