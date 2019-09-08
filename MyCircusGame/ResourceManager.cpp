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

	string basePath = "Resource\\Circus\\";
	
	resPath.push_back(basePath + "number0.bmp");
	resPath.push_back(basePath + "number1.bmp");
	resPath.push_back(basePath + "number2.bmp");
	resPath.push_back(basePath + "number3.bmp");
	resPath.push_back(basePath + "number4.bmp");
	resPath.push_back(basePath + "number5.bmp");
	resPath.push_back(basePath + "number6.bmp");
	resPath.push_back(basePath + "number7.bmp");
	resPath.push_back(basePath + "number8.bmp");
	resPath.push_back(basePath + "number9.bmp");

	resPath.push_back(basePath + "back.bmp");
	resPath.push_back(basePath + "back_deco.bmp");
	resPath.push_back(basePath + "back_normal.bmp");
	resPath.push_back(basePath + "miter.bmp");

	resPath.push_back(basePath + "enemy.bmp");
	resPath.push_back(basePath + "enemy1.bmp");

	resPath.push_back(basePath + "Player0.bmp");
	resPath.push_back(basePath + "Player1.bmp");
	resPath.push_back(basePath + "Player2.bmp");
	resPath.push_back(basePath + "die.bmp");
	resPath.push_back(basePath + "wating.bmp");

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