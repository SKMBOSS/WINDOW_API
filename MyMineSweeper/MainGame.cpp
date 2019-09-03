#include "MainGame.h"
#include "macro.h"
#include "ResManager.h"
#include "Block.h"
#include "BitMap.h"
#include "MyUtility.h"

MainGame* MainGame::m_sThis = nullptr;

MainGame::MainGame()
{
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

	SetVecHeightAndWidth(10, 10);
	SetMineNum(10);

	m_pSelect = nullptr;

	SetVecBlock();
	ShuffleMine();
	SetBlockNumber();
}

void MainGame::Update()
{
	//InvalidateRect(m_hWnd, NULL, true);
}

void MainGame::Input(POINT pt)
{
	for (int i = 0; i < m_iVecHeight; i++)
	{
		for (int j = 0; j < m_iVecWidth; j++)
		{
			Block *targetBlock = m_vecBlock.at((m_iVecWidth * (i)) + (j));

			if (targetBlock->Input(pt))
			{
				m_pSelect = targetBlock;

				if (targetBlock->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_0))
				{
					ClickBlockEmpty(i, j);
				}
				InvalidateRect(m_hWnd, NULL, true);
			}
		}
	}
}

void MainGame::ClickBlockEmpty(int i, int j)
{
	//공통동작 : open


	//종료조건 : 호출한곳이 빈곳이 아닐때
	if (!IsOutOfRangeIndex(j, i, m_iVecWidth, m_iVecHeight))
	{
		if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
			->GetBlockFront() != m_pResManager->GetBitMap(RES_TYPE_BLOCK_0))
		{
			if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
				->GetBlockFront() != m_pResManager->GetBitMap(RES_TYPE_BLOCK_MINE))
			{
				//지뢰가 아니라면 오픈하고
				m_vecBlock.at((m_iVecWidth * (i)) + (j))->SetOpen();
			}
			return;
		}
	}

	//누른곳이 빈곳이면
	if (m_vecBlock.at((m_iVecWidth * (i)) + (j))
		->GetBlockFront() == m_pResManager->GetBitMap(RES_TYPE_BLOCK_0))
	{
		m_vecBlock.at((m_iVecWidth * (i)) + (j))->SetOpen();


		//재귀 8방향
		if (!IsOutOfRangeIndex(j - 1, i - 1, m_iVecWidth, m_iVecHeight))
		{
			if (!m_vecBlock.at((m_iVecWidth * (i - 1)) + (j - 1))->IsOpen())
			{
				ClickBlockEmpty(i - 1, j - 1);
			}
		}
		if (!IsOutOfRangeIndex(j, i -1, m_iVecWidth, m_iVecHeight))
		{
			if (!m_vecBlock.at((m_iVecWidth * (i - 1)) + (j))->IsOpen())
			{
				ClickBlockEmpty(i - 1, j - 1);
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
			if (m_vecBlock.at((m_iVecWidth * (i + 1)) + (j + 1))->IsOpen())
			{
				ClickBlockEmpty(i + 1, j + 1);
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
			if (!IsOutOfRangeIndex(j,i, m_iVecWidth, m_iVecHeight))
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
			if (!IsOutOfRangeIndex(j + 1, i -1, m_iVecWidth, m_iVecHeight))
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
			if (!IsOutOfRangeIndex(j - 1, i+ 1, m_iVecWidth, m_iVecHeight))
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

