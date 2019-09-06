#include "BackGround.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

int BackGround::m_sBackGroundNumber = 0;

BackGround::BackGround()
{
	m_iThisNum = m_sBackGroundNumber++;
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	CircusObject::SetObjectPos(0, 180);

	if (m_iThisNum != 4)
	{
		m_pTopBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK_NORMAL);
	}
	else
	{
		m_pTopBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK_DECO);
	}
	m_topPos.x = m_iThisNum * m_pTopBitMap->GetSize().cx;
	m_topPos.y = 100;

	m_pBottomBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK);
	m_bottomPos.x = m_iThisNum * m_pBottomBitMap->GetSize().cx;
	m_bottomPos.y = 180;

	m_speed = 2;
	m_eState = BG_IDLE;
	m_bMove = false;
}

void BackGround::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		if (!m_bMove)
		{
			m_bMove = true;
		}
		m_eState = BG_FRONT;
		break;
	case VK_RIGHT:
		m_eState = BG_BACK;
		break;
	}
}

void BackGround::TerminateInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_bMove = false;
		m_eState = BG_IDLE;
		break;
	}
}

void BackGround::Update()
{
	if (m_eState == BG_FRONT)
	{
		if (m_topPos.x >= (m_pTopBitMap->GetSize().cx * (m_sBackGroundNumber - 1)) - m_speed)
			m_topPos.x = m_pTopBitMap->GetSize().cx * -1;

		if (m_bottomPos.x >= (m_pTopBitMap->GetSize().cx *(m_sBackGroundNumber - 1)) - m_speed)
			m_bottomPos.x = m_pTopBitMap->GetSize().cx * -1;

		m_topPos.x += m_speed;
		m_bottomPos.x += m_speed;
	}
	else if (m_eState == BG_BACK)
	{
		if (m_topPos.x <= m_pTopBitMap->GetSize().cx * -1 + m_speed)
			m_topPos.x = m_pTopBitMap->GetSize().cx * (m_sBackGroundNumber - 1);

		if (m_bottomPos.x <= m_pTopBitMap->GetSize().cx * -1 + m_speed)
			m_bottomPos.x = m_pTopBitMap->GetSize().cx * (m_sBackGroundNumber - 1);

		m_topPos.x -= m_speed;
		m_bottomPos.x -= m_speed;
	}

	


	

	
}
void BackGround::Draw(HDC hdc)
{
	m_pTopBitMap->Draw(hdc, m_topPos);
	m_pBottomBitMap->Draw(hdc, m_bottomPos);
}
void BackGround::Release()
{
	SAFE_DELETE(m_pBottomBitMap);
}