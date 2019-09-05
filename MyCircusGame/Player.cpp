#include "Player.h"
#include "Macro.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include <time.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	CircusObject::SetObjectPos(1, 325);
	m_eState = WAIT;
	SetStateBitMap();
	m_inputStartTime = 0;
	m_bMove = false;
}

void Player::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		m_bMove = true;
		if (m_eState == WAIT)
		{
			m_eState = BACK;
		}
		else if (m_eState == BACK)
		{
			m_eState = WAIT;
		}
		break;
	case VK_RIGHT:
		m_bMove = true;
		if (m_eState == WAIT)
		{
			m_eState = FRONT;
		}
		else if (m_eState == FRONT)
		{
			m_eState = BACK;
		}
		else if (m_eState == BACK)
		{
			m_eState = WAIT;
		}
		break;
	}
}

void Player::TerminateInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_bMove = false;
		m_eState = WAIT;
		SetStateBitMap();
		break;
	}
}

void Player::Update()
{
	SetInputStartTime();
	DelaySetBitMap(100);
}
void Player::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, CircusObject::m_Pos);
}

void Player::Release()
{
	SAFE_DELETE(m_pBitMap);
}

void Player::SetStateBitMap()
{
	switch (m_eState)
	{
	case WAIT:
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
		break;
	case BACK:
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_01);
		break;
	case FRONT:
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_02);
		break;
	}
}

void Player::DelaySetBitMap(int time)
{
	while (GetTickCount() - m_inputStartTime < 100)//0.1ÃÊ
	{
		SetStateBitMap();
	}
}

void Player::SetInputStartTime()
{
	if (m_bMove)
	{
		m_inputStartTime = GetTickCount();
	}
	else
	{
		m_inputStartTime = 0;
	}
}
