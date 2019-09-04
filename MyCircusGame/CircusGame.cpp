#include "CircusGame.h"
#include "BitMap.h"
#include "Stage01.h"

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
	test = new Stage01();
	test->Init(hWnd, hdc);
}
void CircusGame::Input(WPARAM wParam)
{
	test->Input(wParam);
}
void CircusGame::Update()
{
	test->Update();
}
void CircusGame::Draw(HDC hdc)
{
	test->Draw(hdc);
}
void CircusGame::Release()
{
	delete test;
}