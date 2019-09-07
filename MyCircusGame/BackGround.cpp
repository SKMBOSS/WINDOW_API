#include "BackGround.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

int BackGround::m_sBackGroundNumber = -1;

BackGround::BackGround()
{
	m_iThisNum = m_sBackGroundNumber++;
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	if (m_iThisNum != 4)
		m_pTopBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK_NORMAL);
	else
		m_pTopBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK_DECO);
	m_pBottomBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK);

	m_iBackPosX = m_iThisNum * GetThisBackGroundSizeX();
	m_iTopBackPosY = 100;
	m_iBottomBackPosY = 180;
	m_speed = 2;
	m_eState = BG_IDLE;
}

void BackGround::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		m_eState = BG_BACK;
		break;
	case VK_RIGHT:
		m_eState = BG_FRONT;
		break;
	}
}

void BackGround::TerminateInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_eState = BG_IDLE;
		break;
	}
}

void BackGround::Update()
{
	int iCheckSection = (m_iThisNum + 1) *  GetThisBackGroundSizeX();
	int iCycle = (CircusObject::m_sScreenPosX / GetWholeBackGroundSizeX());

	if (m_eState == BG_FRONT 
		&& CircusObject::m_sScreenPosX == iCheckSection + (iCycle * GetWholeBackGroundSizeX()))
	{
		m_iBackPosX += GetWholeBackGroundSizeX();
	}

	else if (m_eState == BG_BACK 
		&& CircusObject::m_sScreenPosX == iCheckSection + (iCycle * GetWholeBackGroundSizeX()))
	{
		m_iBackPosX -= GetWholeBackGroundSizeX();
	}
}

void BackGround::Draw(HDC hdc)
{
	int iActualOutputX = m_iBackPosX - CircusObject::m_sScreenPosX;

	m_pTopBitMap->Draw(hdc, iActualOutputX, m_iTopBackPosY);
	m_pBottomBitMap->Draw(hdc, iActualOutputX, m_iBottomBackPosY);
}
void BackGround::Release()
{
	SAFE_DELETE(m_pTopBitMap);
	SAFE_DELETE(m_pBottomBitMap);
}

int BackGround::GetThisBackGroundSizeX()
{
	return m_pTopBitMap->GetSize().cx;
}

int BackGround::GetWholeBackGroundSizeX()
{
	return GetThisBackGroundSizeX() * (m_sBackGroundNumber);
}
