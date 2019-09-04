#include "MainGame.h"
#include "macro.h"
#include "ResManager.h"
#include "Block.h"
#include "BitMap.h"
#include "MyUtility.h"

MainGame* MainGame::m_sThis = nullptr;

MainGame::MainGame()
{
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

	m_pSelect = nullptr;

	m_pBackGround = m_pResManager->GetBitMap(RES_TYPE_BACKGROUND);

	SetVecHeightAndWidth(10, 10);
	SetMineNum(10);
	SetTime();

	m_eState = GAME_STATE_PLAY;
	SetVecBlock();
	ShuffleMine();
	SetBlockNumber();
}

void MainGame::Update()
{
	if (m_eState == GAME_STATE_PLAY)
	{
		if(IsWin())
			m_eState = GAME_STATE_WIN;

		if (m_iTimeCount == 0)
		{
			m_iTime++;
			m_iTimeCount = 10;
			InvalidateRect(m_hWnd, NULL, true);
		}
		m_iTimeCount--;
	}

	else if (m_eState == GAME_STATE_LOSE)
	{
		m_eState = GAME_STATE_WAIT;
		if (MessageBox(m_hWnd, "당신은 졌습니다", "YOU DIE", MB_OK))
		{
			m_iFlagNum = m_iMineNum;
			DeleteVecBlock();
			SetVecBlock();
			ShuffleMine();
			SetBlockNumber();
			m_eState = GAME_STATE_PLAY;
			InvalidateRect(m_hWnd, NULL, true);
		}
	}
	else if (m_eState == GAME_STATE_WIN)
	{
		m_eState = GAME_STATE_WAIT;
		if (MessageBox(m_hWnd, "축하합니다!", "YOU WIN", MB_OK))
		{
			m_iFlagNum = m_iMineNum;
			DeleteVecBlock();
			SetVecBlock();
			ShuffleMine();
			SetBlockNumber();
			m_eState = GAME_STATE_PLAY;
			InvalidateRect(m_hWnd, NULL, true);
		}
	}
}

void MainGame::LBInput(POINT pt)
{
	if (m_eState == GAME_STATE_PLAY)
	{
		for (int i = 0; i < m_iVecHeight; i++)
		{
			for (int j = 0; j < m_iVecWidth; j++)
			{
				m_pSelect = m_vecBlock.at((m_iVecWidth * (i)) + (j));

				if (m_pSelect->LBInput(pt))
				{
					if (m_pSelect->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_0))
					{
						ClickBlockEmpty(i, j);
					}
					else if (m_pSelect->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
					{
						AllOpen();
						InvalidateRect(m_hWnd, NULL, true);
						m_eState = GAME_STATE_LOSE;
					}
					InvalidateRect(m_hWnd, NULL, true);
				}
			}
		}
	}
}

void MainGame::RbInput(POINT pt)
{
	if (m_eState == GAME_STATE_PLAY)
	{
		for (int i = 0; i < m_iVecHeight; i++)
		{
			for (int j = 0; j < m_iVecWidth; j++)
			{
				m_pSelect = m_vecBlock.at((m_iVecWidth * (i)) + (j));

				if (m_pSelect->RbInput(pt))
				{
					if (m_pSelect->IsFlag())
					{
						m_pSelect->SetBlockBack(m_pResManager->GetBitMap(RES_TYPE_BLOCK_FLAG));
						m_iFlagNum--;
					}

					else
					{
						m_pSelect->SetBlockBack(m_pResManager->GetBitMap(RES_TYPE_BLOCK_BACK));
						m_iFlagNum++;
					}
					InvalidateRect(m_hWnd, NULL, true);
				}
			}
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

	DrawMineNum(hdc);
	DrawTime(hdc);
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
				nullptr,
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
	m_iFlagNum = num;
}

void MainGame::SetTime()
{
	m_iTime = 0;
}

void MainGame::ShuffleMine()
{
	int shuffleCount = m_iMineNum;
	while (shuffleCount > 0)
	{
		int randomMinePos = rand() % (m_iVecWidth * m_iVecHeight);

		if (m_vecBlock[randomMinePos]
			->GetBlockFront() != m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
		{
			m_vecBlock[randomMinePos]
				->SetBlockFront(m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE));

			shuffleCount--;
		}
	}
}

void MainGame::SetBlockNumber()
{
	int number = 0;
	for (int i = 0; i < m_iVecHeight; i++)
	{
		for (int j = 0; j < m_iVecWidth; j++)
		{
			if (!IsOutOfRangeIndex(j, i, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					continue;
				}
			}
			if (!IsOutOfRangeIndex(j - 1, i - 1, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i - 1)) + (j - 1))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j, i - 1, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i - 1)) + (j))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j + 1, i - 1, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i - 1)) + (j + 1))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j - 1, i, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i)) + (j - 1))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j + 1, i, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i)) + (j + 1))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j - 1, i + 1, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i + 1)) + (j - 1))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j, i + 1, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i + 1)) + (j))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}
			if (!IsOutOfRangeIndex(j + 1, i + 1, m_iVecWidth, m_iVecHeight))
			{
				if (m_vecBlock.at((m_iVecWidth * (i + 1)) + (j + 1))
					->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
				{
					number++;
				}
			}

			m_vecBlock.at((m_iVecWidth * (i)) + (j))
				->SetBlockFront(m_pResManager->GetBitMap(number));

			number = 0;
		}
	}
}

void MainGame::ClickBlockEmpty(int i, int j)
{
	if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
		->GetBlockFront() != m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
	{//지뢰가 아니라면 오픈하고
		m_vecBlock.at((m_iVecWidth * (i)) + (j))->SetOpen();
		//플래그세워있으면 회수하고
		if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
			->GetBlockBack() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_FLAG))
		{
			m_iFlagNum++;
		}

		for (int numberBlockIndex = 1; numberBlockIndex <= 8; numberBlockIndex++)
		{
			if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
				->GetBlockFront() == m_pResManager->GetBitMap(numberBlockIndex))
			{//종료조건 : 호출한곳이 1~8일때
				return;
			}
		}
	}

	//재귀 8방향
	if (!IsOutOfRangeIndex(j - 1, i - 1, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i - 1)) + (j - 1))->IsOpen())
		{
			ClickBlockEmpty(i - 1, j - 1);
		}
	}
	if (!IsOutOfRangeIndex(j, i - 1, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i - 1)) + (j))->IsOpen())
		{
			ClickBlockEmpty(i - 1, j);
		}
	}
	if (!IsOutOfRangeIndex(j + 1, i - 1, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i - 1)) + (j + 1))->IsOpen())
		{
			ClickBlockEmpty(i - 1, j + 1);
		}
	}
	if (!IsOutOfRangeIndex(j - 1, i, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i)) + (j - 1))->IsOpen())
		{
			ClickBlockEmpty(i, j - 1);
		}
	}
	if (!IsOutOfRangeIndex(j + 1, i, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i)) + (j + 1))->IsOpen())
		{
			ClickBlockEmpty(i, j + 1);
		}
	}
	if (!IsOutOfRangeIndex(j - 1, i + 1, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i + 1)) + (j - 1))->IsOpen())
		{
			ClickBlockEmpty(i + 1, j - 1);
		}
	}
	if (!IsOutOfRangeIndex(j, i + 1, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i + 1)) + (j))->IsOpen())
		{
			ClickBlockEmpty(i + 1, j);
		}
	}
	if (!IsOutOfRangeIndex(j + 1, i + 1, m_iVecWidth, m_iVecHeight))
	{
		if (!m_vecBlock.at((m_iVecWidth * (i + 1)) + (j + 1))->IsOpen())
		{
			ClickBlockEmpty(i + 1, j + 1);
		}
	}
}

void MainGame::DrawMineNum(HDC hdc)
{
	TCHAR szBuf[128];
	wsprintf(szBuf, TEXT("%d"), m_iFlagNum);
	TextOut(hdc, 675, 480, szBuf, lstrlen(szBuf));
}

void MainGame::DrawTime(HDC hdc)
{
	TCHAR szBuf[128];
	wsprintf(szBuf, TEXT("%d"), m_iTime);
	TextOut(hdc, 170, 480, szBuf, lstrlen(szBuf));
}

bool MainGame::IsWin()
{
	int count = m_vecBlock.size() - m_iMineNum;

	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); ++iter)
	{
		if ((*iter)->IsOpen() == true)
			count--;
	}
	if (count == 0)
		return true;

	return false;
}

void MainGame::AllOpen()
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); ++iter)
	{
		(*iter)->SetOpen();
	}
}

