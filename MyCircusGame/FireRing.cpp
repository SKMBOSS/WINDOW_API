#include "FireRing.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <time.h>

int FireRing::m_sFireRingNumber = 0;

FireRing::FireRing()
{
	miThisNumber = m_sFireRingNumber++;
}

FireRing::~FireRing()
{

}

void FireRing::Init()
{
	m_inputStartTime = GetTickCount();
	m_bIsOnScreen = false;
	m_Pos.x = 0;
	m_Pos.y = 182;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_FIRE_0);
}

void FireRing::Input(WPARAM wParam)
{
}

void FireRing::TerminateInput(WPARAM wParam)
{
}

void FireRing::Update()
{
	if (m_bIsOnScreen)
	{
		if (GetTickCount() % 20 == 0)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_FIRE_1);
		else if (GetTickCount() % 20 == 10)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_FIRE_0);

		m_Pos.x -= 1;

		if (m_Pos.x < CircusObject::m_sScreenPosX - 64)
		{
			m_bIsOnScreen = false;
			m_inputStartTime = GetTickCount();
		}
	}
	else
	{
		int iSpawnTime = rand() % 1000 + (2000 * miThisNumber);
		if (GetTickCount() - m_inputStartTime  >= iSpawnTime)
		{
			m_Pos.x = CircusObject::m_sScreenPosX + 640* (miThisNumber+1);
			m_bIsOnScreen = true;
		}
	}
}

void FireRing::Draw(HDC hdc)
{
	if (m_bIsOnScreen && CircusObject::m_sScreenPosX <= 5500)
	{
		int iActualOutputX = m_Pos.x - CircusObject::m_sScreenPosX;
		m_pBitMap->Draw(hdc, iActualOutputX, m_Pos.y);
	}
}

void FireRing::Release()
{
	SAFE_DELETE(m_pBitMap);
}

RECT FireRing::GetCollisonBox()
{
	SIZE size = m_pBitMap->GetSize();

	RECT CB = { m_Pos.x+10 , m_Pos.y + size.cy-2, m_Pos.x + size.cx-10, m_Pos.y + size.cy };
	return CB;
}

void FireRing::ReStart()
{
	Init();
}