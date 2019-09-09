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

	resPath.push_back(basePath + "block01.bmp");
	resPath.push_back(basePath + "block02.bmp");
	resPath.push_back(basePath + "block03.bmp");
	resPath.push_back(basePath + "block04.bmp");
	resPath.push_back(basePath + "block05.bmp");
	resPath.push_back(basePath + "block06.bmp");
	resPath.push_back(basePath + "block07.bmp");
	resPath.push_back(basePath + "block08.bmp");
	resPath.push_back(basePath + "block09.bmp");
	resPath.push_back(basePath + "block10.bmp");
	resPath.push_back(basePath + "block11.bmp");
	resPath.push_back(basePath + "block12.bmp");
	resPath.push_back(basePath + "block13.bmp");
	resPath.push_back(basePath + "block14.bmp");
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