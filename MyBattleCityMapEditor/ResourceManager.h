#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_BLOCK_DEFAULT,
	RES_BLOCK_NOMAR_FULL,
	RES_BLOCK_NOMAR_TOP,
	RES_BLOCK_NOMAR_BOT,
	RES_BLOCK_NOMAR_LEFT,
	RES_BLOCK_NOMAR_RIGHT,

	RES_BLOCK_METAL_FULL,
	RES_BLOCK_METAL_TOP,
	RES_BLOCK_METAL_BOT,
	RES_BLOCK_METAL_LEFT,
	RES_BLOCK_METAL_RIGHT,

	RES_BLOCK_ICE,
	RES_BLOCK_FOREST,
	RES_BLOCK_WATER,

	RES_BLOCK_NORMAL_BOT_LEFT,
	RES_BLOCK_NORMAL_BOT_RIGHT,

	RES_BLOCK_LIFE,

	RES_TYPE_END
};

class BitMap;
class ResourceManager
{
private:
	static ResourceManager* m_sThis;
	BitMap* m_pBitMap[RES_TYPE_END];
	vector<string> resPath;
public:
	static ResourceManager* GetInstance();
	BitMap* GetBitMap(int index);
	SIZE GetBitMapSize(int index);
private:
	void InitResPath();
	void InitBitMap(HDC hdc);
public:
	void Init(HDC hdc);
	void Release();
private:
	ResourceManager();
public:
	~ResourceManager();
};

