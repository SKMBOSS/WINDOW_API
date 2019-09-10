#pragma once
#include <Windows.h>

enum BLOCK_TYPE
{
	DEFAULT,
	BLOCK_00,
	BLOCK_01,
	BLOCK_02,
	BLOCK_03,
	BLOCK_04,
	BLOCK_05,
	BLOCK_06,
	BLOCK_07,
	BLOCK_08,
	BLOCK_09,
	BLOCK_10,
	BLOCK_11,
	BLOCK_12,
	BLOCK_13,
	BLOCK_14
};

class BitMap;
class Block
{
private:
	static int			m_sBlockNumber;
	static BLOCK_TYPE	m_SelectBlockType;
	int					miThisNumber;
	POINT				m_Pos;
	BitMap*				m_pBitMap;
public:
	void Init();
	void Input(POINT pt);
	void InputR(POINT pt);
	void Update();
	void Draw(HDC hdc);
	void Release();
public:
	Block();
	virtual ~Block();
};

