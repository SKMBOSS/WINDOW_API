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
	tb = new TextBrick();
	tb->Init();
}
void Intro::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_RETURN:
		SceneManager::GetInstance()->ChangeScene(SCENE_STATE::MAIN_GAME);
	}
}
void Intro::Update()
{
	tb->Update();
}
void Intro::Render(HDC hdc)
{
	tb->Render(hdc);
}
void Intro::Release()
{
	delete tb;
}