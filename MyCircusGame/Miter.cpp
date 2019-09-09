#include "Miter.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <cmath>

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

	m_iMiter = 100;
	SetDigitNumberBitMap(m_iMiter, m_pNumber, 3);
}

void Miter::Input(WPARAM wParam)
{
	//
}

void Miter::TerminateInput(WPARAM wParam)
{
	//
}

void Miter::Update()
{
	int iCheckSection = 20 + m_pBitMap->GetSize().cx;
	int iCycle = (CircusObject::m_sScreenPosX / 640);

	if (CircusObject::m_sScreenPosX == iCheckSection + (iCycle * 640))
	{
		m_Pos.x += 640 * CircusObject::GetDirection();
		m_iMiter -= 10 * CircusObject::GetDirection();
		SetDigitNumberBitMap(m_iMiter, m_pNumber, 3);
	}
}

void Miter::Draw(HDC hdc)
{
	int iActualOutputX = m_Pos.x - CircusObject::m_sScreenPosX;
	m_pBitMap->Draw(hdc, iActualOutputX, m_Pos.y);

	for (int i = 0; i < 3; i++)
	{
		m_pNumber[i] ->Draw(hdc, iActualOutputX + 14*(i+1), 408 + 12);
	}
}

void Miter::Release()
{
	SAFE_DELETE(m_pBitMap);
}


BitMap* Miter::GetNumberBitMap(int num)
{
	if (num == 0)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER0);

	else if (num == 1)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER1);

	else if (num == 2)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER2);

	else if (num == 3)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER3);

	else if (num == 4)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER4);

	else if (num == 5)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER5);

	else if (num == 6)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER6);

	else if (num == 7)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER7);

	else if (num == 8)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER8);

	else if (num == 9)
		return ResourceManager::GetInstance()->GetBitMap(RES_TYPE_NUMBER9);

	else
		return nullptr;
}

void Miter::SetDigitNumberBitMap(int num, BitMap* arrBitMap[], int size)
{
	int iTemp = num;

	arrBitMap[size - 1] = GetNumberBitMap(iTemp % 10);

	for (int i = 0; i < size - 1; i++)
	{
		int iPowNum = size - 1;
		int iDigit = pow(10, iPowNum - i);

		arrBitMap[i] = GetNumberBitMap(iTemp / iDigit);

		if (iTemp / 10 != 0)
		{
			iTemp %= iDigit;
		}
	}
}