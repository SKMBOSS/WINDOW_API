#include "Block.h"
#include "BitMap.h"

Block::Block()
{
	m_bOpen = false;
	m_bFlag = false;
}

Block::~Block()
{
}

void Block::SetBlockFront(BitMap* pBitMap)
{
	m_pBitMap = pBitMap;
}

BitMap* Block::GetBlockFront()
{
	return m_pBitMap;
}

BitMap* Block::GetBlockBack()
{
	return m_pBackBitMap;
}

void Block::SetBlockBack(BitMap* pBitMap)
{
	m_pBackBitMap = pBitMap;
}

void Block::Init(BitMap* pBitMap, BitMap* pBackBitMap, int x, int y)
{
	m_pBitMap = pBitMap;
	m_pBackBitMap = pBackBitMap;
	m_iX = x;
	m_iY = y;
}

void Block::Draw(HDC hdc)
{
	if (m_bOpen)
		m_pBitMap->Draw(hdc, m_iX, m_iY);
	else
		m_pBackBitMap->Draw(hdc, m_iX, m_iY);
}

bool Block::LBInput(POINT pt)
{
	if (m_bOpen || m_bFlag)
		return false;

	RECT rc = { m_iX  , m_iY , m_iX + m_pBitMap->GetSize().cx  , m_iY + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt))
	{
		m_bOpen = true;
		return true;
	}

	return false;
}

bool Block::RbInput(POINT pt)
{
	if (m_bOpen)
		return false;

	RECT rc = { m_iX  , m_iY , m_iX + m_pBitMap->GetSize().cx  , m_iY + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt))
	{
		return true;
	}
	return false;
}
