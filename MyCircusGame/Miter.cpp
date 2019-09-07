#include "Miter.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

Miter::Miter()
{
}

Miter::~Miter()
{
}

void Miter::Init()
{
	m_Pos.x = 20;
	m_Pos.y = 408;
	m_eState = MITER_IDLE;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK_MITER);
}

void Miter::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		m_eState = MITER_BACK;
		break;
	case VK_RIGHT:
		m_eState = MITER_FRONT;
		break;
	}
}

void Miter::TerminateInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_eState = MITER_IDLE;
		break;
	}
}

void Miter::Update()
{
	int iCheckSection = 20;
	int iCycle = (CircusObject::m_sScreenPosX / 640);

	if (m_eState == MITER_FRONT
		&& CircusObject::m_sScreenPosX == iCheckSection + (iCycle * 640))
	{
		m_Pos.x += 640;
	}

	else if (m_eState == MITER_BACK
		&& CircusObject::m_sScreenPosX == iCheckSection + (iCycle * 640))
	{
		m_Pos.x -= 640;
	}
}

void Miter::Draw(HDC hdc)
{
	int iActualOutputX = m_Pos.x - CircusObject::m_sScreenPosX;
	m_pBitMap->Draw(hdc, iActualOutputX, m_Pos.y);
}

void Miter::Release()
{
	SAFE_DELETE(m_pBitMap);
}
