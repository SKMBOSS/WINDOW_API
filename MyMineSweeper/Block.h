#pragma once
#include <Windows.h>

class BitMap;
class Block
{
private:
	BitMap*		m_pBitMap;
	BitMap*		m_pBackBitMap;
	int			m_iX;
	int			m_iY;
	bool		m_bOpen;
	bool		m_bFlag;
public:
	inline void SetOpen()
	{
		m_bOpen = true;
	}
	inline bool IsOpen()
	{
		return m_bOpen;
	}
	inline bool IsFlag()
	{
		if (m_bFlag == false)
			m_bFlag = true;
		else
			m_bFlag = false;

		return m_bFlag;
	}

public:
	void SetBlockFront(BitMap* pBitMap);
	void SetBlockBack(BitMap* pBitMap);
	BitMap* GetBlockFront();
	void Init(BitMap* pBitMap, BitMap* pBackBitMap, int x, int y);
	void Draw(HDC hdc);
	bool LBInput(POINT pt);
	bool RbInput(POINT pt);
public:
	Block();
	~Block();
};

