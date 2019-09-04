#include "CircusGame.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include "Stage01.h"
#include "Macro.h"

CircusGame* CircusGame::m_sThis = nullptr;

CircusGame::CircusGame()
{
}

CircusGame::~CircusGame()
{
}

CircusGame* CircusGame::GetInstance()
{
	if (m_sThis == nullptr)
		m_sThis = new CircusGame();

	return m_sThis;
}

void CircusGame::Init(HWND hWnd, HDC hdc)
{
	ResourceManager::GetInstance()->Init(hdc);
	SceneManager::GetInstance()->Init(hWnd, hdc);
}

void CircusGame::Input(WPARAM wParam)
{
	SceneManager::GetInstance()->Input(wParam);
}

void CircusGame::Update()
{
	SceneManager::GetInstance()->Update();
}

void CircusGame::Draw(HDC hdc)
{
	SceneManager::GetInstance()->Draw(hdc);
}

void CircusGame::Release()
{
	ResourceManager::GetInstance()->Release();
	SceneManager::GetInstance()->Release();
	SAFE_DELETE(m_sThis);
}