#include "FireRing.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <time.h>


FireRing::FireRing()
{
	m_Pos.x = 500;
	m_Pos.y = 182;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_ENEMY_00);

	m_eState = FR_FRONT;
}

FireRing::~FireRing()
{

}

void FireRing::Init()
{
}

void FireRing::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		m_eState = FR_BACK;
		break;
	}
}

void FireRing::TerminateInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_eState = FR_FRONT;
		break;
	}
}

void FireRing::Update()
{
	if (m_eState == FR_FRONT)
	{
		m_Pos.x -= 1;
		if (m_Pos.x <= 2) m_Pos.x = 400;
	}

	else if (m_eState == FR_BACK)
	{
		m_Pos.x += 1;
	}

}

void FireRing::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_Pos.x, m_Pos.y);
}

void FireRing::Release()
{
	SAFE_DELETE(m_pBitMap);
}

