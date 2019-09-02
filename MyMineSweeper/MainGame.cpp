#include "MainGame.h"
#include "macro.h"
#include "ResManager.h"
#include "Block.h"

MainGame* MainGame::m_sThis = nullptr;

MainGame::MainGame()
{
	m_pResManager = nullptr;
	m_eState = GAME_STATE_WAIT;

	m_pSelectOne = nullptr;
	m_pSelectTwo = nullptr;

	m_dwCount = 0;
}

MainGame::~MainGame()
{
}

void MainGame::Init(HWND hWnd, HDC hdc, HINSTANCE hInst)
{
	m_hWnd = hWnd;
	srand(GetTickCount());

	m_pResManager = new ResManager();
	m_pResManager->Init(hdc, hInst);

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

	for (int i = 0; i < 100; i++)
	{
		Block* pNew = new Block();
		pNew->Init(m_pResManager->GetBitMap(RES_TYPE_00), m_pResManager->GetBitMap(RES_TYPE_BACK),
			(i % 10) * 25 + 10 * (i % 10), 
			(i / 10) * 25 + 10 * (i / 10)
			);

		m_vecBlock.push_back(pNew);
	}

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
	InvalidateRect(m_hWnd, NULL, true);
}

void MainGame::Input(POINT pt)
{
	/*if (m_eState == GAME_STATE_SHOW)
		return;

	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		if ((*iter)->Input(pt))
		{
			if (m_eState == GAME_STATE_WAIT)
			{
				m_pSelectOne = *iter;
				m_eState = GAME_STATE_ONE;
			}
			else if (m_eState == GAME_STATE_ONE)
			{
				m_pSelectTwo = *iter;
				if (m_pSelectTwo->GetID() == m_pSelectOne->GetID())
				{
					m_eState = GAME_STATE_WAIT;
				}
				else
				{
					m_eState = GAME_STATE_SHOW;
				}
			}

			InvalidateRect(m_hWnd, NULL, true);
		}
	}*/
}

void MainGame::Draw(HDC hdc)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		(*iter)->Draw(hdc);
	}
}

void MainGame::Release()
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	m_vecBlock.clear();

	SAFE_DELETE(m_pResManager);
	SAFE_DELETE(m_sThis);
}
