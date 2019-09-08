#pragma once
#include "ResourceManager.h"
#include "BitMap.h"
#include <cmath>

BitMap* GetNumberBitMap(int num)
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

void SetDigitNumberBitMap(int num, BitMap* arrBitMap[], int size)
{
	int iTemp = num;

	arrBitMap[size - 1] = GetNumberBitMap(iTemp % 10);

	for (int i = 0; i < size-1; i++)
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
