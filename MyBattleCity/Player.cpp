#include "Player.h"
#include "Global.h"
#include "BitMap.h"
#include "ResourceManager.h"
#include <time.h>
#include "Tile.h"

Player::Player()
{
}

Player::Player(list<Tile*>* listTile)
{
	SetStartInfo();
	m_listTile = listTile;
}

Player::~Player()
{
}

void Player::Update(float fElapseTime)
{
	OperateInput();
	UpdatePos(fElapseTime);
	UpdateBitMap();
}

void Player::Render()
{
	m_pBitmap->RenderCheck(m_posX, m_posY);
	m_pBitmap->Render(m_posX + 20, m_posY + 20);
}

void Player::SetStartInfo()
{
	m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
	m_posX = TILE4_SIZE * 4 + TILE1_SIZE;
	m_posY = TILE4_SIZE * 12;
	m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
	m_eState = TANK_IDLE;
	m_startInputTime = 0;
}

void Player::OperateInput()
{
	//Å°´­¸²
	if (GetKeyState(VK_UP) & 0x8000)
	{
		if (m_eState == TANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = TANK_UP;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if (m_eState == TANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = TANK_DOWN;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_DOWN_00);
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (m_eState == TANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = TANK_LEFT;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_LEFT_00);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_eState == TANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = TANK_RIGHT;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_RIGHT_00);
	}
	//Å°¶À
	else if (GetAsyncKeyState(VK_LEFT) & 0x0001 || GetAsyncKeyState(VK_RIGHT) & 0x0001 ||
		GetAsyncKeyState(VK_UP) & 0x0001 || GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		m_eState = TANK_IDLE;
	}

}

void Player::UpdatePos(float fElapseTime)
{
	switch (m_eState)
	{
	case TANK_IDLE:
		break;
	case TANK_UP:
		if ((LONG)m_posY ==0)
			break;
		m_posY -= TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posY += TILE4_SIZE * fElapseTime * 2;
		break;
	case TANK_DOWN:
		if ((LONG)m_posY == TILE4_SIZE * (TILE4_COL - 1))
			break;
		m_posY += TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posY -= TILE4_SIZE * fElapseTime * 2;;
		break;
	case TANK_LEFT:
		if ((LONG)m_posX == 0)
			break;
		m_posX -= TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posX += TILE4_SIZE * fElapseTime * 2;;
		break;
	case TANK_RIGHT:
		if ((LONG)m_posX == TILE4_SIZE * (TILE4_ROW - 1))
			break;
		m_posX += TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posX -= TILE4_SIZE * fElapseTime * 2;
		break;
	default:
		break;
	}
	m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
}
void Player::UpdateBitMap()
{
	switch (m_eState)
	{
	case TANK_IDLE:
		break;
	case TANK_UP:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
		break;
	case TANK_DOWN:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_DOWN_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_DOWN_00);
		break;
	case TANK_LEFT:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_LEFT_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_LEFT_00);
		break;
	case TANK_RIGHT:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_RIGHT_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_RIGHT_00);
		break;
	default:
		break;
	}
}

bool Player::CollisionCheck()
{
	for (auto iter = m_listTile->begin(); iter != m_listTile->end(); ++iter)
	{
		RECT temp;
		if (IntersectRect(&temp, &(*iter)->GetCollisionRECT(), &m_collisionRECT))
		{
			return true;
		}
	}
	return false;
}