#include "Block.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

int Block::m_sBlockNumber = 0;
BLOCK_TYPE Block::m_SelectBlockType = BLOCK_NORMAL_FULL;

Block::Block()
{
	miThisNumber = m_sBlockNumber++;
	m_eState = BLOCK_DEFAULT;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_DEFAULT);
	m_bNoCLickZone = false;
}

Block::~Block()
{

}

void Block::Init()
{
	m_Pos.x = ((miThisNumber % 13) * m_pBitMap->GetSize().cx);
	m_Pos.y = ((miThisNumber / 13) * m_pBitMap->GetSize().cy);

	if (miThisNumber == 13 * 12 + 5)
	{
		m_eState = BLOCK_NORMAL_RIGHT;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_NORMAL_RIGHT);
		m_bNoCLickZone = true;
	}

	else if (miThisNumber == 13 * 11 + 5)
	{
		m_eState = BLOCK_NORMAL_BOT_RIGHT;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_NORMAL_BOT_RIGHT);
		m_bNoCLickZone = true;
	}

	else if (miThisNumber == 13 * 11 + 6)
	{
		m_eState = BLOCK_NORMAL_BOT;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_NORMAL_BOT);
		m_bNoCLickZone = true;
	}

	else if (miThisNumber == 13 * 11 + 7)
	{
		m_eState = BLOCK_NORMAL_BOT_LEFT;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_NORMAL_BOT_LEFT);
		m_bNoCLickZone = true;
	}

	else if (miThisNumber == 13 * 12 + 7)
	{
		m_eState = BLOCK_NORMAL_LEFT;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_NORMAL_LEFT);
		m_bNoCLickZone = true;
	}
	else if (miThisNumber == 13 * 12 + 6)
	{
		m_eState = BLOCK_LIFE;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_LIFE);
		m_bNoCLickZone = true;
	}
}

void Block::Input(POINT pt)
{
	pt.x -= 20;
	pt.y -= 20;
	RECT rc = { m_Pos.x , m_Pos.y , m_Pos.x + m_pBitMap->GetSize().cx  , m_Pos.y + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt) && !m_bNoCLickZone)
	{
		m_eState = m_SelectBlockType;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(m_SelectBlockType);
	}
}

void Block::InputR(POINT pt)
{
	pt.x -= 20;
	pt.y -= 20;
	RECT rc = { m_Pos.x , m_Pos.y , m_Pos.x + m_pBitMap->GetSize().cx  , m_Pos.y + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt) && !m_bNoCLickZone)
	{
		m_eState = BLOCK_DEFAULT;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_DEFAULT);
	}
}

void Block::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_Pos.x, m_Pos.y);
}

BLOCK_TYPE Block::GetType()
{
	return m_eState;
}

void Block::SetBitMap(int type)
{
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(type);
}