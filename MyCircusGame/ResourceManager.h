#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_TYPE_BACK,
	RES_TYPE_PLAYER,
	RES_TYPE_END
};

class BitMap;
class ResourceManager
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
	ResourceManager();
	~ResourceManager();
};

