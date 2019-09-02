#include "GameManager.h"
#include "MainGame.h"

GameManager* GameManager::m_sThis = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

GameManager* GameManager::GetInstance()
{
	if (m_sThis == nullptr)
		m_sThis = new GameManager();

	return m_sThis;
}

void GameManager::SetGameMode(GAME_MODE eMode)
{
	if (eMode == GAME_MODE_EASY)
		MainGame::GetInstance()->SetVecHeightAndWidth(10,10);
	else if (eMode == GAME_MODE_NOMAL)
		MainGame::GetInstance()->SetVecHeightAndWidth(15,15);
	else if (eMode == GAME_MODE_HARD)
		MainGame::GetInstance()->SetVecHeightAndWidth(20,20);

	MainGame::GetInstance()->DeleteVecBlock();
	MainGame::GetInstance()->SetVecBlock();
}