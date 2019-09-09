#include "WinFloor.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <time.h>

WinFloor::WinFloor()
{
}

WinFloor::~WinFloor()
{
}

void WinFloor::Init()
{
	m_Pos.x = 6424;
	m_Pos.y = 358;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_WIN_FLOOR);
}

void WinFloor::Input(WPARAM wParam)
{
}

void WinFloor::TerminateInput(WPARAM wParam)
{
}

void WinFloor::Update()
{
}

void WinFloor::Draw(HDC hdc)
{
	int iActualOutputX = m_Pos.x - CircusObject::m_sScreenPosX;
	m_pBitMap->Draw(hdc, iActualOutputX, m_Pos.y);
}

void WinFloor::Release()
{
	SAFE_DELETE(m_pBitMap);
}

RECT WinFloor::GetCollisonBox()
{
	SIZE size = m_pBitMap->GetSize();

	RECT CB = { m_Pos.x , m_Pos.y-5, m_Pos.x + size.cx , m_Pos.y + size.cy };
	return CB;
}