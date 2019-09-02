#include "ResManager.h"
#include "BitMap.h"
#include "resource.h"
#include "macro.h"

ResManager::ResManager()
{
	InitResPath();
}


ResManager::~ResManager()
{
}


void ResManager::Init(HDC hdc)
{
	InitBitMap(hdc);
}

BitMap* ResManager::GetBitMap(int index)
{
	//배열 검사

	return m_pBitMap[index];
}

SIZE ResManager::GetBitMapSize(int index)
{
	return m_pBitMap[index]->GetSize();
}

void ResManager::Release()
{
	for (int i = 0; i < RES_TYPE_END; i++)
	{
		SAFE_DELETE(m_pBitMap[i]);
	}
}

void ResManager::InitResPath()
{
	resPath.reserve(RES_TYPE_END);

	string basePath = "res\\Mine\\";

	resPath.push_back(basePath + "block_0.bmp");
	resPath.push_back(basePath + "block_1.bmp");
	resPath.push_back(basePath + "block_2.bmp");
	resPath.push_back(basePath + "block_3.bmp");
	resPath.push_back(basePath + "block_4.bmp");
	resPath.push_back(basePath + "block_5.bmp");
	resPath.push_back(basePath + "block_6.bmp");
	resPath.push_back(basePath + "block_7.bmp");
	resPath.push_back(basePath + "block_8.bmp");
	resPath.push_back(basePath + "mine.bmp");
	resPath.push_back(basePath + "flag.bmp");
	resPath.push_back(basePath + "block.bmp");
	resPath.push_back(basePath + "back.bmp");
}

void ResManager::InitBitMap(HDC hdc)
{
	for (int i = 0; i < RES_TYPE_END; i++)
	{
		m_pBitMap[i] = new BitMap();
		m_pBitMap[i]->Init(hdc, resPath[i]);
	}
}