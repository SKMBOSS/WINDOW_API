#include "Block.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

int Block::m_sBlockNumber = 0;
BLOCK_TYPE Block::m_SelectBlockType = BLOCK_NORMAL_FULL;

Block::Block()
{
	miThisNumber = m_sBlockNumber++;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_DEFAULT);
}

Block::~Block()
{

}

void Block::Init()
{
	m_Pos.x = ((miThisNumber%13) * m_pBitMap->GetSize().cx);
	m_Pos.y = ((miThisNumber/13) * m_pBitMap->GetSize().cy);
}

void Block::Input(POINT pt)
{
	pt.x -= 20;
	pt.y -= 20;
	RECT rc = { m_Pos.x , m_Pos.y , m_Pos.x + m_pBitMap->GetSize().cx  , m_Pos.y + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt))
	{
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(m_SelectBlockType);
	}
}

void Block::InputR(POINT pt)
{
	pt.x -= 20;
	pt.y -= 20;
	RECT rc = { m_Pos.x , m_Pos.y , m_Pos.x + m_pBitMap->GetSize().cx  , m_Pos.y + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt))
	{
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(BLOCK_DEFAULT);
	}
}

void Block::Update()
{

}

void Block::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_Pos.x, m_Pos.y);
}

void Block::Release()
{
	SAFE_DELETE(m_pBitMap);
}
