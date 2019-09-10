#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_TYPE_DEFAULT,
	RES_TYPE_BLOCK_00,//º®µ¹
	RES_TYPE_BLOCK_01,//À§º®µ¹
	RES_TYPE_BLOCK_02,//¿Þº®µ¹
	RES_TYPE_BLOCK_03,//¾Æ·¡º®µ¹
	RES_TYPE_BLOCK_04,//¿À¸¥º®µ¹
	RES_TYPE_BLOCK_05,//Ã¶ÆÇ
	RES_TYPE_BLOCK_06,//½£
	RES_TYPE_BLOCK_07,//¹°
	RES_TYPE_BLOCK_08,//ÀüÃ¼°­Ã¶º®µ¹
	RES_TYPE_BLOCK_09,//À§°­Ã¶
	RES_TYPE_BLOCK_10,//¿Þ°­Ã¶
	RES_TYPE_BLOCK_11,//¾Æ·¡°­Ã¶
	RES_TYPE_BLOCK_12,//¿À¸¥°­Ã¶
	RES_TYPE_BLOCK_13,//µ¶¼ö¸®
	RES_TYPE_BLOCK_14,//µ¶¼ö¸®Á×À½
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

