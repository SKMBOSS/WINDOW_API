#include "BackGround.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

int BackGround::m_sBackGroundNumber = -1;

BackGround::BackGround()
{
	m_sBackGroundNumber++;
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	CircusObject::SetObjectPos(0, 180);

	m_pTopBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK_NORMAL);
	m_topPos.x= m_sBackGroundNumber * 64;
	m_topPos.y = 116;

	m_pBottomBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK);
	m_bottomPos.x = m_sBackGroundNumber * 64;
	m_bottomPos.y = 180;
}

void BackGround::Input(WPARAM wParam)
{
	//
}

void BackGround::TerminateInput(WPARAM wParam)
{
	//
}

void BackGround::Update()
{
	//
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