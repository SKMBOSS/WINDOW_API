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
	{
		MainGame::GetInstance()->SetVecHeightAndWidth(10, 10);
		MainGame::GetInstance()->SetMineNum(10);
	}
	else if (eMode == GAME_MODE_NOMAL)
	{
		MainGame::GetInstance()->SetVecHeightAndWidth(30, 16);
		MainGame::GetInstance()->SetMineNum(30);
	}
	else if (eMode == GAME_MODE_HARD)
	{
		MainGame::GetInstance()->SetVecHeightAndWidth(30, 16);
		MainGame::GetInstance()->SetMineNum(60);
	}

	MainGame::GetInstance()->DeleteVecBlock();
	MainGame::GetInstance()->SetVecBlock();
	MainGame::GetInstance()->ShuffleMine();
	MainGame::GetInstance()->SetBlockNumber();
}