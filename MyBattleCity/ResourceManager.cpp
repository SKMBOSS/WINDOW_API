#include "ResourceManager.h"
#include "BitMap.h"
#include "macro.h"

ResourceManager* ResourceManager::m_sThis = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::GetInstance()
{
	if (m_sThis == nullptr)
		m_sThis = new ResourceManager();

	return m_sThis;
}

void ResourceManager::Init(HDC hdc)
{
	InitResPath();
	InitBitMap(hdc);
}

void ResourceManager::Release()
{
	for (int i = 0; i < RES_TYPE_END; i++)
	{
		SAFE_DELETE(m_pBitMap[i]);
	}
	SAFE_DELETE(m_sThis);
}

void ResourceManager::InitResPath()
{
	resPath.reserve(RES_TYPE_END);

	string basePath = "Resource\\";
	string tile = basePath + "tile\\";
	string backGround = basePath + "backGround\\";
	string tank = basePath + "tank\\";

	resPath.push_back(backGround + "_game_back.bmp");
	resPath.push_back(backGround + "_map_back.bmp");

	resPath.push_back(tile + "_brick.bmp");
	resPath.push_back(tile + "_metal.bmp");
	resPath.push_back(tile + "_ice.bmp");
	resPath.push_back(tile + "_bush.bmp");
	resPath.push_back(tile + "_water.bmp");
	resPath.push_back(tile + "_base.bmp"); 
	resPath.push_back(tile + "_base_broken.bmp");

	resPath.push_back(tank + "_yellow_tank_up_00.bmp");
	resPath.push_back(tank + "_yellow_tank_up_01.bmp");
	resPath.push_back(tank + "_yellow_tank_down_00.bmp");
	resPath.push_back(tank + "_yellow_tank_down_01.bmp");
	resPath.push_back(tank + "_yellow_tank_left_00.bmp");
	resPath.push_back(tank + "_yellow_tank_left_01.bmp");
	resPath.push_back(tank + "_yellow_tank_right_00.bmp");
	resPath.push_back(tank + "_yellow_tank_right_01.bmp");

	/*resPath.push_back(tank + "_gray_tank_up_00.bmp");
	resPath.push_back(tank + "_gray_tank_up_01.bmp");
	resPath.push_back(tank + "_gray_tank_down_00.bmp");
	resPath.push_back(tank + "_gray_tank_down_01.bmp");
	resPath.push_back(tank + "_gray_tank_left_00.bmp");
	resPath.push_back(tank + "_gray_tank_left_01.bmp");
	resPath.push_back(tank + "_gray_tank_right_00.bmp");
	resPath.push_back(tank + "_gray_tank_right_01.bmp");*/
}

void ResourceManager::InitBitMap(HDC hdc)
{
	for (int i = 0; i < RES_TYPE_END; i++)
	{
		m_pBitMap[i] = new BitMap();
		m_pBitMap[i]->Init(hdc, resPath[i]);
	}
}

BitMap* ResourceManager::GetBitMap(int index)
{
	//인덱스검사해야함
	return m_pBitMap[index];
}

SIZE ResourceManager::GetBitMapSize(int index)
{
	return m_pBitMap[index]->GetSize();
}