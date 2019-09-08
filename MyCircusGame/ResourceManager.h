#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

enum RES_TYPE
{
	RES_TYPE_NUMBER0,
	RES_TYPE_NUMBER1,
	RES_TYPE_NUMBER2,
	RES_TYPE_NUMBER3,
	RES_TYPE_NUMBER4,
	RES_TYPE_NUMBER5,
	RES_TYPE_NUMBER6,
	RES_TYPE_NUMBER7,
	RES_TYPE_NUMBER8,
	RES_TYPE_NUMBER9,
	RES_TYPE_BACK,
	RES_TYPE_BACK_DECO,
	RES_TYPE_BACK_NORMAL,
	RES_TYPE_BACK_MITER,
	RES_TYPE_ENEMY_FIRE_0,
	RES_TYPE_ENEMY_FIRE_1,
	RES_TYPE_ENEMY_FIRE_2,
	RES_TYPE_ENEMY_FIRE_3,
	RES_TYPE_PLAYER_00,
	RES_TYPE_PLAYER_01,
	RES_TYPE_PLAYER_02,
	RES_TYPE_PLAYER_DIE,
	RES_TYPE_WAITING_SCENE,
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

