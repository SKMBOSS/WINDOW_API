#include "MyBenechia.h"
#include "SceneManager.h"

MyBenechia::MyBenechia()
{
}

MyBenechia::~MyBenechia()
{
}

void MyBenechia::Init()
{
	SceneManager::GetInstance()->Init();
}

void MyBenechia::Input(WPARAM wParam)
{
	SceneManager::GetInstance()->Input(wParam);
}

void MyBenechia::Update()
{
	SceneManager::GetInstance()->Update();
}

void MyBenechia::Render(HDC hdc)
{
	SceneManager::GetInstance()->Render(hdc);
}

void MyBenechia::Release()
{
	SceneManager::GetInstance()->Release();
}
