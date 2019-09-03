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
public:
	inline void SetOpen()
	{
		m_bOpen = true;
	}
	inline bool IsOpen()
	{
		return m_bOpen;
	}

public:
	void SetBlockFront(BitMap* pBitMap);
	BitMap* GetBlockFront();
	void Init(BitMap* pBitMap, BitMap* pBackBitMap, int x, int y);
	void Draw(HDC hdc);
	bool Input(POINT pt);
public:
	Block();
	~Block();
};

