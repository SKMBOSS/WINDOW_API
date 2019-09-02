#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_TYPE_00,
	RES_TYPE_01,
	RES_TYPE_02,
	RES_TYPE_03,
	RES_TYPE_04,
	RES_TYPE_05,
	RES_TYPE_06,
	RES_TYPE_07,
	RES_TYPE_08,
	RES_TYPE_MINE,
	RES_TYPE_FLAG,
	RES_TYPE_BACK,
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
	void InitBitMap(HDC hdc, HINSTANCE hInst);
public:
	void Init(HDC hdc, HINSTANCE hInst);
	void Release();
	BitMap* GetBitMap(int index);
public:
	ResManager();
	~ResManager();
};

