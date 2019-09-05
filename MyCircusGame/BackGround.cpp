#include "BackGround.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	CircusObject::SetObjectPos(0, 180);
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_BACK);
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
	m_pBitMap->Draw(hdc, CircusObject::m_Pos);
}
void BackGround::Release()
{
	SAFE_DELETE(m_pBitMap);
}