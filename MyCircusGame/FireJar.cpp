#include "FireJar.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <time.h>

int FireJar::m_sFireJarNumber = 0;

FireJar::FireJar()
{
	miThisNumber = m_sFireJarNumber++;
}

FireJar::~FireJar()
{

}

void FireJar::Init()
{
	if (miThisNumber == 0)
		m_Pos.x = 6374;
	else 
	{
		if (CircusObject::m_sScreenPosX <= 5500 - (6 - miThisNumber) * 600 +200)
			m_Pos.x = CircusObject::m_sScreenPosX + 600 * (miThisNumber)+rand() % 200;
		else
			m_Pos.x = -100;
		if (m_Pos.x >= 5900)
			m_Pos.x = -100;
	}
	
	m_Pos.y = 362;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_FIRE_3);
}

void FireJar::Input(WPARAM wParam)
{
}

void FireJar::TerminateInput(WPARAM wParam)
{
}

void FireJar::Update()
{
	if (GetTickCount() % 20 == 0)
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_FIRE_2);
	else if (GetTickCount() % 20 == 10)
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_FIRE_3);
}

void FireJar::Draw(HDC hdc)
{
	int iActualOutputX = m_Pos.x - CircusObject::m_sScreenPosX;
	m_pBitMap->Draw(hdc, iActualOutputX, m_Pos.y);
}

void FireJar::Release()
{
	SAFE_DELETE(m_pBitMap);
}

RECT FireJar::GetCollisonBox()
{
	SIZE size = m_pBitMap->GetSize();

	RECT CB = { m_Pos.x+10, m_Pos.y+15, m_Pos.x + size.cx-10, m_Pos.y + size.cy };
	return CB;
}

void FireJar::ReStart()
{
	Init();
}
