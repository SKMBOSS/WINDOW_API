#pragma once
#include <Windows.h>

enum BLOCK_TYPE
{
	BLOCK_DEFAULT,

	BLOCK_NORMAL_FULL,
	BLOCK_NORMAL_TOP,
	BLOCK_NORMAL_BOT,
	BLOCK_NORMAL_LEFT,
	BLOCK_NORMAL_RIGHT,

	BLOCK_METAL_FULL,
	BLOCK_METAL_TOP,
	BLOCK_METAL_BOT,
	BLOCK_METAL_LEFT,
	BLOCK_METAL_RIGHT,

	BLOCK_ICE,
	BLOCK_FOREST,
	BLOCK_WATER,

	BLOCK_NORMAL_BOT_LEFT,
	BLOCK_NORMAL_BOT_RIGHT,

	BLOCK_LIFE
};

class BitMap;
class Block
{
public :
	static BLOCK_TYPE	m_SelectBlockType;
	static int			m_sBlockNumber;
private:
	int					miThisNumber;
	POINT				m_Pos;
	BitMap*				m_pBitMap;
	bool				m_bNoCLickZone;
	BLOCK_TYPE			m_eState;
public:
	void Init();
	void Input(POINT pt);
	void InputR(POINT pt);
	void Draw(HDC hdc);
	BLOCK_TYPE GetType();
	void SetBitMap(int type);
	
public:
	Block();
	virtual ~Block();
};

