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

	string basePath = "Resource\\BattleCity\\";

	resPath.push_back(basePath + "Tile\\block_default.bmp");

	resPath.push_back(basePath + "Tile\\block_normal_full.bmp");
	resPath.push_back(basePath + "Tile\\block_normal_top.bmp");
	resPath.push_back(basePath + "Tile\\block_normal_bottom.bmp");
	resPath.push_back(basePath + "Tile\\block_normal_left.bmp");
	resPath.push_back(basePath + "Tile\\block_normal_right.bmp");

	resPath.push_back(basePath + "Tile\\block_metal_full.bmp");
	resPath.push_back(basePath + "Tile\\block_metal_top.bmp");
	resPath.push_back(basePath + "Tile\\block_metal_bottom.bmp");
	resPath.push_back(basePath + "Tile\\block_metal_left.bmp");
	resPath.push_back(basePath + "Tile\\block_metal_right.bmp");

	resPath.push_back(basePath + "Tile\\block_ice.bmp");
	resPath.push_back(basePath + "Tile\\block_forest.bmp");
	resPath.push_back(basePath + "Tile\\block_water.bmp");
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