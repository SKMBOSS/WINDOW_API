#include "Stage.h"
#include "Global.h"
#include "Macro.h"
#include "BitMap.h"
#include "ResourceManager.h"
#include "Player.h"
#include "TileMap.h"

Stage::Stage()
{

}

Stage::~Stage()
{
}

void Stage::Init()
{
	m_BackGround = ResourceManager::GetInstance()->GetBitMap(RES_BG_GAME);
	m_mapBackGround = ResourceManager::GetInstance()->GetBitMap(RES_BG_MAP);

	m_pTileMap = new TileMap();
	m_pTileMap->Init();

	m_pPlayer = new Player();
	m_pPlayer->Init(m_pTileMap);
}

void Stage::Update(float fElapseTime)
{
	m_pPlayer->Update(fElapseTime);
}

void Stage::Render()
{
	m_BackGround->Render(0, 0);
	m_mapBackGround->Render(20, 20);

	m_pTileMap->Render();
	m_pPlayer->Render();
}

void Stage::Release()
{
	SAFE_RELEASE(m_pTileMap);
	SAFE_DELETE(m_pTileMap);

	SAFE_DELETE(m_pPlayer);
}
