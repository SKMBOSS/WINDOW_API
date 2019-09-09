#include "ScoreBoard.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <time.h>
#include "MyUtility.h"

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Init()
{
	m_Pos.x = 22;
	m_Pos.y = 20;
	m_BonusTime = GetTickCount();
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_SCORE_BOARD);

	m_iBonus = 5010;
	SetDigitNumberBitMap(m_iBonus, m_pBonus, 4);
}

void ScoreBoard::Input(WPARAM wParam)
{
}

void ScoreBoard::TerminateInput(WPARAM wParam)
{
}

void ScoreBoard::Update()
{
	if ((GetTickCount() - m_BonusTime) % 500 == 0)
		m_iBonus -= 10;

	SetDigitNumberBitMap(m_iBonus, m_pBonus, 4);
}

void ScoreBoard::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_Pos.x, m_Pos.y);

	for (int i = 0; i < 4; i++)
	{
		m_pBonus[i]->Draw(hdc, (m_Pos.x + 269) + 14 * (i), 45);
	}
}

void ScoreBoard::Release()
{
	SAFE_DELETE(m_pBitMap);
}
