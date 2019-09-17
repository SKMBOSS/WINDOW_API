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
	
	m_pBitmap->RenderCheck(m_pos.x, m_pos.y);
	m_pBitmap->Render(m_pos.x + 20, m_pos.y + 20);
}

void Player::SetStartInfo()
{
	m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
	m_pos.x = TILE4_SIZE * 4 + TILE1_SIZE;
	m_pos.y = TILE4_SIZE * 12;
	m_collisionRECT = { m_pos.x+2, m_pos.y+2, m_pos.x + TILE4_SIZE-2, m_pos.y + TILE4_SIZE-2 };
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
		m_pos.y -= TILE4_SIZE * fElapseTime;
		m_collisionRECT = { m_pos.x + 2, m_pos.y + 2, m_pos.x + TILE4_SIZE - 2, m_pos.y + TILE4_SIZE - 2 };
		if (CollisionCheck())
			m_pos.y += 1;
		break;
	case TANK_DOWN:
		if (m_pos.y == TILE4_SIZE * (TILE4_COL - 1))
			break;
		m_pos.y += TILE4_SIZE * 3 * fElapseTime;
		m_collisionRECT = { m_pos.x + 2, m_pos.y + 2, m_pos.x + TILE4_SIZE - 2, m_pos.y + TILE4_SIZE - 2 };
		if (CollisionCheck())
			m_pos.y -= 1;
		
		break;
	case TANK_LEFT:
		m_pos.x -= TILE4_SIZE * fElapseTime;
		m_collisionRECT = { m_pos.x + 2, m_pos.y + 2, m_pos.x + TILE4_SIZE - 2, m_pos.y + TILE4_SIZE - 2 };
		if (CollisionCheck())
			m_pos.x += 1;
		break;
	case TANK_RIGHT:
		if (m_pos.x == TILE4_SIZE * (TILE4_ROW - 1))
			break;
		m_pos.x += TILE4_SIZE * 3 * fElapseTime;
		m_collisionRECT = { m_pos.x + 2, m_pos.y + 2, m_pos.x + TILE4_SIZE - 2, m_pos.y + TILE4_SIZE - 2 };
		if (CollisionCheck())
			m_pos.x -= 1;
		break;
	default:
		break;
	}
	m_collisionRECT = { m_pos.x + 2, m_pos.y + 2, m_pos.x + TILE4_SIZE - 2, m_pos.y + TILE4_SIZE - 2 };
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