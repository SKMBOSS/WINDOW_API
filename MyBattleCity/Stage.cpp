#include "Stage.h"
#include "Macro.h"
#include "Tile.h"
#include "Brick.h"
#include "Metal.h"
#include <fstream>
#include <iostream>
#include "BitMap.h"
#include "ResourceManager.h"
#include "Global.h"
#include "Base.h"
#include "Player.h"

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

	LoadTile();

	m_pPlayer = new Player(&m_listTile);
}

void Stage::Update(float fElapseTime)
{
	m_pPlayer->Update(fElapseTime);
}

void Stage::Render()
{
	m_BackGround->Render(0, 0);
	m_mapBackGround->Render(20, 20);

	for (auto iter = m_listTile.begin(); iter != m_listTile.end(); iter++)
		(*iter)->Render();

	m_pPlayer->Render();
}

void Stage::Release()
{
	for (auto iter = m_listTile.begin(); iter != m_listTile.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	m_listTile.clear();

	SAFE_DELETE(m_pPlayer);
}

void Stage::LoadTile()
{
	ifstream readFile("Resource\\map\\stage01.txt");
	int iTileType;
	Tile* upLeft;
	Tile* upRight;
	Tile* downLeft;
	Tile* downRight;
	for (int i = 0; i < TILE4_COL; i++)
	{
		for (int j = 0; j < TILE4_ROW; j++)
		{
			readFile >> iTileType;
			//¾öÃ»³ª°Ù±º
			switch (iTileType)
			{
			case TILE_BRICK_FULL:
				upLeft = new Brick(j * TILE4_SIZE , i * TILE4_SIZE );
				upRight = new Brick(j * TILE4_SIZE + TILE1_SIZE , i * TILE4_SIZE );
				downLeft = new Brick(j * TILE4_SIZE , i * TILE4_SIZE + TILE1_SIZE );
				downRight = new Brick(j * TILE4_SIZE + TILE1_SIZE , i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(upLeft);
				m_listTile.push_back(upRight);
				m_listTile.push_back(downLeft);
				m_listTile.push_back(downRight);
				break;
			case TILE_BRICK_TOP:
				upLeft = new Brick(j * TILE4_SIZE, i * TILE4_SIZE );
				upRight = new Brick(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE );
				m_listTile.push_back(upLeft);
				m_listTile.push_back(upRight);
				break;
			case TILE_BRICK_BOT:
				downLeft = new Brick(j * TILE4_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				downRight = new Brick(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(downLeft);
				m_listTile.push_back(downRight);
				break;
			case TILE_BRICK_LEFT:
				upLeft = new Brick(j * TILE4_SIZE, i * TILE4_SIZE );
				downLeft = new Brick(j * TILE4_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(upLeft);
				m_listTile.push_back(downLeft);
				break;
			case TILE_BRICK_RIGHT:
				upRight = new Brick(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE );
				downRight = new Brick(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(upRight);
				m_listTile.push_back(downRight);
				break;
			case TILE_BRICK_BOT_LEFT:
				downLeft = new Brick(j * TILE4_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(downLeft);
				break;
			case TILE_BRICK_BOT_RIGHT:
				downRight = new Brick(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(downRight);
				break;
			case TILE_METAL_FULL:
				upLeft = new Metal(j * TILE4_SIZE, i * TILE4_SIZE );
				upRight = new Metal(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE );
				downLeft = new Metal(j * TILE4_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				downRight = new Metal(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(upLeft);
				m_listTile.push_back(upRight);
				m_listTile.push_back(downLeft);
				m_listTile.push_back(downRight);
				break;
			case TILE_METAL_TOP:
				upLeft = new Metal(j * TILE4_SIZE, i * TILE4_SIZE );
				upRight = new Metal(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE );
				m_listTile.push_back(upLeft);
				m_listTile.push_back(upRight);
				break;
			case TILE_METAL_BOT:
				downLeft = new Metal(j * TILE4_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				downRight = new Metal(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(downLeft);
				m_listTile.push_back(downRight);
				break;
			case TILE_METAL_LEFT:
				upLeft = new Metal(j * TILE4_SIZE, i * TILE4_SIZE );
				downLeft = new Metal(j * TILE4_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(upLeft);
				m_listTile.push_back(downLeft);
				break;
			case TILE_METAL_RIGHT:
				upRight = new Metal(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE );
				downRight = new Metal(j * TILE4_SIZE + TILE1_SIZE, i * TILE4_SIZE + TILE1_SIZE );
				m_listTile.push_back(upRight);
				m_listTile.push_back(downRight);
				break;
			case TILE_LIFE:
				upLeft = new Base(j * TILE4_SIZE, i * TILE4_SIZE);
				m_listTile.push_back(upLeft);
			case TILE_DEFAULT:
			default:
				break;
			}
		}
	}
}