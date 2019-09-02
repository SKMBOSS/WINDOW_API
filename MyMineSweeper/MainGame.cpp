#include "MainGame.h"
#include "macro.h"
#include "ResManager.h"
#include "Block.h"
#include "BitMap.h"

MainGame* MainGame::m_sThis = nullptr;

MainGame::MainGame()
{
	m_pResManager = nullptr;
	m_pSelect = nullptr;
	m_pBackGround = nullptr;
	SetVecHeightAndWidth(10, 10);
	SetMineNum(10);
	//m_eState = GAME_STATE_WAIT;
}

MainGame::~MainGame()
{
}

MainGame* MainGame::GetInstance()
{
	if (m_sThis == nullptr)
		m_sThis = new MainGame();

	return m_sThis;
}

void MainGame::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;
	srand(GetTickCount());

	m_pResManager = new ResManager();
	m_pResManager->Init(hdc);

	m_pBackGround = m_pResManager->GetBitMap(RES_TYPE_BACKGROUND);

	/*int iArray[20];

	for (int i = 0; i < 20; i++)
		iArray[i] = i % 10;

	for (int i = 0; i < 100; i++)
	{
		int randA = rand() % 20;
		int randB = rand() % 20;

		int iTemp = iArray[randA];
		iArray[randA] = iArray[randB];
		iArray[randB] = iTemp;
	}*/

	SetVecBlock();

}

void MainGame::Update()
{
	//if (m_eState != GAME_STATE_SHOW)
	//	return;

	//m_dwCount++;

	//if (m_dwCount == 100)
	//{
	//	m_dwCount = 0;
	//	m_pSelectOne->SetClose();
	//	m_pSelectTwo->SetClose();
	//	m_pSelectOne = nullptr;
	//	m_pSelectTwo = nullptr;
	//	m_eState = GAME_STATE_WAIT;
	//	InvalidateRect(m_hWnd, NULL, true);
	//}
	//InvalidateRect(m_hWnd, NULL, true);
}

void MainGame::Input(POINT pt)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		if ((*iter)->Input(pt))
		{
			m_pSelect = *iter;
			InvalidateRect(m_hWnd, NULL, true);
		}
	}
}

void MainGame::Draw(HDC hdc)
{
	m_pBackGround->Draw(hdc, 0, 0);

	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		(*iter)->Draw(hdc);
	}
}

void MainGame::Release()
{
	DeleteVecBlock();
	SAFE_RELEASE(m_pResManager);
	SAFE_DELETE(m_pResManager);
	SAFE_DELETE(m_sThis);
}

void MainGame::SetVecHeightAndWidth(int height, int width)
{
	m_iVecHeight = height;
	m_iVecWidth = width;
}

void MainGame::SetVecBlock()
{
	for (int i = 0; i < m_iVecHeight; i++)
	{
		for (int j = 0; j < m_iVecWidth; j++)
		{
			Block* pNew = new Block();
			pNew->Init
			(
				m_pResManager->GetBitMap(RES_TYPE_BLOCK_0),
				m_pResManager->GetBitMap(RES_TYPE_BLOCK_BACK),
				i * m_pResManager->GetBitMapSize(RES_TYPE_BLOCK_BACK).cx + 44,
				j * m_pResManager->GetBitMapSize(RES_TYPE_BLOCK_BACK).cy + 46
			);
			m_vecBlock.push_back(pNew);
		}
	}
}

void MainGame::DeleteVecBlock()
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	m_vecBlock.clear();
}

void MainGame::SetMineNum(int num)
{
	m_iMineNum = num;
}