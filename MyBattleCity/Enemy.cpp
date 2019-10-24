#include "Enemy.h"
#include "Global.h"
#include "BitMap.h"
#include "ResourceManager.h"
#include <time.h>
#include "Tile.h"

Enemy::Enemy()
{
}

Enemy::Enemy(list<Tile*>* listTile)
{
	SetStartInfo();
	m_listTile = listTile;
	m_BulletGoing = false;
	m_BulletEffectOn = false;
	srand(GetTickCount());
	m_iSavedKey = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float fElapseTime)
{
	OperateInput();
	UpdatePos(fElapseTime);
	UpdateBitMap();
	UpdateBullet(fElapseTime);

	if (m_startEffectTime)
	{
		if (GetTickCount() - m_startEffectTime >= 0)
			m_pBulletEffectBitMap = ResourceManager::GetInstance()->GetBitMap(RES_EFFECT_EXPLOSION_00);
		if (GetTickCount() - m_startEffectTime >= 50)
			m_pBulletEffectBitMap = ResourceManager::GetInstance()->GetBitMap(RES_EFFECT_EXPLOSION_01);
		if (GetTickCount() - m_startEffectTime >= 100)
			m_pBulletEffectBitMap = ResourceManager::GetInstance()->GetBitMap(RES_EFFECT_EXPLOSION_02);

		if (GetTickCount() - m_startEffectTime >= 150)
			m_startEffectTime = false;
	}
}

void Enemy::Render()
{
	m_pBitmap->RenderCheck(m_posX, m_posY);
	m_pBitmap->Render(m_posX + 20, m_posY + 20);

	if (m_BulletGoing)
		m_pBulletBitMap->Render(m_BulletPosX + 20, m_BulletPosY + 20);

	if (m_startEffectTime)
		m_pBulletEffectBitMap->Render(m_BulletEffectPosX + 20, m_BulletEffectPosY + 20);
}

void Enemy::SetStartInfo()
{
	m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
	m_posX = TILE4_SIZE * 0 + TILE1_SIZE;
	m_posY = TILE4_SIZE * 0;
	m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
	m_eState = ETANK_IDLE;
	m_eBUlletState = EBULLET_UP;
	m_startInputTime = 0;
}

void Enemy::OperateInput()
{
	BulletInput();
	//Å°´­¸²
	int iKey = 99;
	if(GetTickCount() % 100 ==0)
		iKey = rand() % 5;

	if (iKey == ETANK_UP)
	{
		if (m_eState == ETANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = ETANK_UP;
		if (!m_BulletGoing)
			m_eBUlletState = EBULLET_UP;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
	}
	else if (iKey == ETANK_DOWN)
	{
		if (m_eState == ETANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = ETANK_DOWN;
		if (!m_BulletGoing)
			m_eBUlletState = EBULLET_DOWN;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_DOWN_00);
	}
	else if (iKey == ETANK_LEFT)
	{
		if (m_eState == ETANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = ETANK_LEFT;
		if (!m_BulletGoing)
			m_eBUlletState = EBULLET_LEFT;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_LEFT_00);
	}
	else if (iKey == ETANK_RIGHT)
	{
		if (m_eState == ETANK_IDLE)
			m_startInputTime = GetTickCount();
		m_eState = ETANK_RIGHT;
		if (!m_BulletGoing)
			m_eBUlletState = EBULLET_RIGHT;
		m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_RIGHT_00);
	}
	//Å°¶À
	else if (iKey == ETANK_IDLE)
	{
		m_eState = ETANK_IDLE;
	}
}

void Enemy::UpdatePos(float fElapseTime)
{
	switch (m_eState)
	{
	case ETANK_IDLE:
		break;
	case ETANK_UP:
		if ((LONG)m_posY == 0)
			break;
		m_posY -= TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posY += TILE4_SIZE * fElapseTime * 2;
		break;
	case ETANK_DOWN:
		if ((LONG)m_posY == TILE4_SIZE * (TILE4_COL - 1))
			break;
		m_posY += TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posY -= TILE4_SIZE * fElapseTime * 2;;
		break;
	case ETANK_LEFT:
		if ((LONG)m_posX == 0)
			break;
		m_posX -= TILE4_SIZE * fElapseTime * 2;
		m_collisionRECT = { (LONG)m_posX + 1, (LONG)m_posY + 1, (LONG)m_posX + TILE4_SIZE - 1, (LONG)m_posY + TILE4_SIZE - 1 };
		if (CollisionCheck())
			m_posX += TILE4_SIZE * fElapseTime * 2;;
		break;
	case ETANK_RIGHT:
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

void Enemy::UpdateBitMap()
{
	switch (m_eState)
	{
	case ETANK_IDLE:
		break;
	case ETANK_UP:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_UP_00);
		break;
	case ETANK_DOWN:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_DOWN_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_DOWN_00);
		break;
	case ETANK_LEFT:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_LEFT_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_LEFT_00);
		break;
	case ETANK_RIGHT:
		if ((GetTickCount() - m_startInputTime) % 2 == 0)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_RIGHT_01);
		else if ((GetTickCount() - m_startInputTime) % 2 == 1)
			m_pBitmap = ResourceManager::GetInstance()->GetBitMap(RES_TANK_PLAYER1_RIGHT_00);
		break;
	default:
		break;
	}
}

bool Enemy::CollisionCheck()
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

void Enemy::BulletInput()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{

		m_eBUlletState2 = m_eBUlletState;
		switch (m_eBUlletState)
		{
		case EBULLET_UP:
			if (!m_BulletGoing)
			{
				m_pBulletBitMap = ResourceManager::GetInstance()->GetBitMap(RES_BULLET_UP);
				m_BulletPosX = m_posX + 8;
				m_BulletPosY = m_posY;
				m_BulletGoing = true;
			}
			break;
		case EBULLET_DOWN:
			if (!m_BulletGoing)
			{
				m_pBulletBitMap = ResourceManager::GetInstance()->GetBitMap(RES_BULLET_DOWN);
				m_BulletPosX = m_posX + 8;
				m_BulletPosY = m_posY + 16;
				m_BulletGoing = true;
			}
			break;
		case EBULLET_LEFT:
			if (!m_BulletGoing)
			{
				m_pBulletBitMap = ResourceManager::GetInstance()->GetBitMap(RES_BULLET_LEFT);
				m_BulletPosX = m_posX;
				m_BulletPosY = m_posY + 8;
				m_BulletGoing = true;
			}
			break;
		case EBULLET_RIGHT:
			if (!m_BulletGoing)
			{
				m_pBulletBitMap = ResourceManager::GetInstance()->GetBitMap(RES_BULLET_RIGHT);
				m_BulletPosX = m_posX + 8;
				m_BulletPosY = m_posY + 8;
				m_BulletGoing = true;
			}
			break;
		default:
			break;
		}
	}
}

void Enemy::UpdateBullet(float fElapseTime)
{
	if (m_BulletGoing)
	{
		switch (m_eBUlletState2)
		{
		case EBULLET_UP:
			if ((LONG)m_BulletPosY <= 0)
			{
				m_startEffectTime = GetTickCount();
				m_BulletEffectOn = true;
				m_BulletEffectPosX = m_BulletPosX - 8;
				m_BulletEffectPosY = m_BulletPosY - 4;
				m_BulletGoing = false;
			}
			m_BulletPosY -= 200 * fElapseTime;
			break;
		case EBULLET_DOWN:
			if ((LONG)m_BulletPosY >= TILE4_SIZE * (TILE4_ROW - 1) + 16)
			{
				m_startEffectTime = GetTickCount();
				m_BulletEffectOn = true;
				m_BulletEffectPosX = m_BulletPosX - 8;
				m_BulletEffectPosY = m_BulletPosY - 4;
				m_BulletGoing = false;
			}
			m_BulletPosY += 200 * fElapseTime;
			break;
		case EBULLET_LEFT:
			if ((LONG)m_BulletPosX <= 0)
			{
				m_startEffectTime = GetTickCount();
				m_BulletEffectOn = true;
				m_BulletEffectPosX = m_BulletPosX - 8;
				m_BulletEffectPosY = m_BulletPosY - 4;
				m_BulletGoing = false;
			}
			m_BulletPosX -= 200 * fElapseTime;
			break;
		case EBULLET_RIGHT:
			if ((LONG)m_BulletPosX >= TILE4_SIZE * (TILE4_ROW - 1) + 16)
			{
				m_startEffectTime = GetTickCount();
				m_BulletEffectOn = true;
				m_BulletEffectPosX = m_BulletPosX - 8;
				m_BulletEffectPosY = m_BulletPosY - 4;
				m_BulletGoing = false;
			}
			m_BulletPosX += 200 * fElapseTime;
			break;
		default:
			break;
		}
		m_BulletCollisionRECT = { (LONG)m_BulletPosX, (LONG)m_BulletPosY, (LONG)m_BulletPosX + 16, (LONG)m_BulletPosY + 16 };
		BulletCollisionCheck();
	}
}

void Enemy::BulletCollisionCheck()
{
	RECT temp;
	for (auto iter = m_listTile->begin(); iter != m_listTile->end(); ++iter)
	{
		if (IntersectRect(&temp, &(*iter)->GetCollisionRECT(), &m_BulletCollisionRECT))
		{
			if (m_BulletGoing)
			{
				m_startEffectTime = GetTickCount();
				m_BulletEffectOn = true;
				m_BulletEffectPosX = m_BulletPosX - 8;
				m_BulletEffectPosY = m_BulletPosY - 4;

				m_BulletGoing = false;
			}
			m_listTile->erase(iter);
		}
	}
}