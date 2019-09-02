#include "Block.h"
#include "BitMap.h"

Block::Block()
{
	m_bOpen = false;
}

Block::~Block()
{
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

bool Block::Input(POINT pt)
{
	if (m_bOpen)
		return false;
	RECT rc = { m_iX  , m_iY , m_iX + m_pBitMap->GetSize().cx  , m_iY + m_pBitMap->GetSize().cy };

	if (PtInRect(&rc, pt))
	{
		m_bOpen = true;
		return true;
	}

	return false;
}
