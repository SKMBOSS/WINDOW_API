#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_TYPE_BLOCK_0,
	RES_TYPE_BLOCK_1,
	RES_TYPE_BLOCK_2,
	RES_TYPE_BLOCK_3,
	RES_TYPE_BLOCK_4,
	RES_TYPE_BLOCK_5,
	RES_TYPE_BLOCK_6,
	RES_TYPE_BLOCK_7,
	RES_TYPE_BLOCK_8,
	RES_TYPE_BLOCK_MINE,
	RES_TYPE_BLOCK_FLAG,
	RES_TYPE_BLOCK_BACK,
	RES_TYPE_BACKGROUND,
	RES_TYPE_END
};

class BitMap;
class ResManager
{
private:
	BitMap* m_pBitMap[RES_TYPE_END];
	vector<string> resPath;
private:
	void InitResPath();
	void InitBitMap(HDC hdc);
public:
	void Init(HDC hdc);
	void Release();
	BitMap* GetBitMap(int index);
	SIZE GetBitMapSize(int index);
public:
	ResManager();
	~ResManager();
};

