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
	m_Pos.x = 70;
	m_Pos.y = 325;
	m_eState = PL_IDLE;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
	m_inputStartTime = 0;
	m_speed = CircusObject::m_sScreenSpeed;
	m_bOnAnimator = false;
	m_bJump = false;
	m_iMaxJumpCount = 70;
	m_iJumpConut = m_iMaxJumpCount;
}

void Player::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		if (m_eState == PL_JUMPUP || m_eState == PL_JUMP_FRONT 
			|| m_eState == PL_JUMP_BACK || m_eState == PL_DIE)
			break;
		if (m_eState == PL_IDLE)
		{
			m_inputStartTime = GetTickCount();
		}
		m_eState = PL_BACK;
		break;
	case VK_RIGHT:
		if (m_eState == PL_JUMPUP || m_eState == PL_JUMP_FRONT 
			|| m_eState == PL_JUMP_BACK || m_eState == PL_DIE)
			break;
		if (m_eState == PL_IDLE)
		{
			m_inputStartTime = GetTickCount();
		}
		m_eState = PL_FRONT;
		break;
	case VK_SPACE:
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_02);
		if (wParam == VK_SPACE && (GetKeyState(VK_RIGHT) < 0))
		{
			if (m_eState == PL_FRONT)
			{
				m_inputStartTime = GetTickCount();
				m_eState = PL_JUMP_FRONT;
			}
		}
		else if (wParam == VK_SPACE && (GetKeyState(VK_LEFT) < 0))
		{
			if (m_eState == PL_BACK)
			{
				m_inputStartTime = GetTickCount();
				m_eState = PL_JUMP_BACK;
			}
		}
		if (m_eState == PL_IDLE)
		{
			m_inputStartTime = GetTickCount();
			m_eState = PL_JUMPUP;
		}
	}
}

void Player::TerminateInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		if (m_eState == PL_JUMPUP || m_eState == PL_JUMP_FRONT 
			|| m_eState == PL_JUMP_BACK || m_eState == PL_DIE)
			break;
		m_bOnAnimator = false;
		m_eState = PL_IDLE;
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
		break;
	}
}

void Player::Update()
{
	if (m_eState == PL_FRONT && m_Pos.x <= 6500)
	{
		if (m_Pos.x <= 5758 + 246 + 70)
		{
			CircusObject::m_sSavedPosX = CircusObject::m_sScreenPosX;
			CircusObject::MoveScreenRight();
		}
		m_Pos.x += m_speed;

		if (!m_bOnAnimator)
		{
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_01);
			m_bOnAnimator = true;
		}
		if ((GetTickCount() - m_inputStartTime) % 30 == 0)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_01);
		else if ((GetTickCount() - m_inputStartTime) % 30 == 10)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_02);
		else if ((GetTickCount() - m_inputStartTime) % 30 == 20)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
	}

	else if (m_eState == PL_BACK && m_Pos.x >= 72)
	{
		if (m_Pos.x <= 5760 + 246 + 70)
		{
			CircusObject::m_sSavedPosX = CircusObject::m_sScreenPosX;
			CircusObject::MoveScreenLeft();
		}

		m_Pos.x -= m_speed;
		if (!m_bOnAnimator)
		{
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_01);
			m_bOnAnimator = true;
		}
		if ((GetTickCount() - m_inputStartTime) % 20 == 0)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_01);
		else if ((GetTickCount() - m_inputStartTime) % 20 == 10)
			m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
	}

	else if (m_eState == PL_JUMPUP)
	{
		
		if (m_iJumpConut >= 35)
		{
			m_Pos.y -= 3;
		}
		else if (m_iJumpConut < 35)
		{
			m_Pos.y += 3;
			if (m_iJumpConut == 0)
			{
				m_eState = PL_IDLE;
				m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
				if (GetKeyState(VK_RIGHT) < 0)
					m_eState = PL_FRONT;
				else if (GetKeyState(VK_LEFT) < 0)
					m_eState = PL_BACK;
				m_iJumpConut = m_iMaxJumpCount;
			}
		}
		m_iJumpConut--;
	}

	else if (m_eState == PL_JUMP_FRONT && m_Pos.x <= 6500)
	{
		if (m_Pos.x <= 5758 + 246 + 70)
			CircusObject::MoveScreenRight();

		if (m_iJumpConut >= 35)
		{
			m_Pos.y -= 3;
			m_Pos.x += 2;
		}
		else if (m_iJumpConut < 35)
		{
			m_Pos.y += 3;
			m_Pos.x += 2;
			if (m_iJumpConut == 0)
			{
				m_eState = PL_IDLE;
				m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
				if(GetKeyState(VK_RIGHT) < 0)
					m_eState = PL_FRONT;
				else if (GetKeyState(VK_LEFT) < 0)
					m_eState = PL_BACK;
				m_iJumpConut = m_iMaxJumpCount;
			}
		}
		m_iJumpConut--;
	}

	else if (m_eState == PL_JUMP_BACK && m_Pos.x >= 72)
	{
		if (m_Pos.x <= 5760 + 246 + 70)
			CircusObject::MoveScreenLeft();

		if (m_iJumpConut >= 35)
		{
			m_Pos.y -= 3;
			m_Pos.x -= 2;
		}
		else if (m_iJumpConut < 35)
		{
			m_Pos.y += 3;
			m_Pos.x -= 2;
			if (m_iJumpConut == 0)
			{
				m_eState = PL_IDLE;
				m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
				if (GetKeyState(VK_RIGHT) < 0)
					m_eState = PL_FRONT;
				else if (GetKeyState(VK_LEFT) < 0)
					m_eState = PL_BACK;
				m_iJumpConut = m_iMaxJumpCount;
			}
		}
		m_iJumpConut--;
	}
}

void Player::Draw(HDC hdc)
{
	int iActualOutputX = m_Pos.x - CircusObject::m_sScreenPosX;

	m_pBitMap->Draw(hdc, iActualOutputX, m_Pos.y);

	TCHAR szBuf[128];
	wsprintf(szBuf, TEXT("플레이어 :%d"), m_Pos.x);
	TextOut(hdc, 200, 120, szBuf, lstrlen(szBuf));

	TCHAR szBuf2[128];
	wsprintf(szBuf2, TEXT("스크린 :%d"), CircusObject::m_sScreenPosX);
	TextOut(hdc, 200, 140, szBuf2, lstrlen(szBuf2));

	TCHAR szBuf3[128];
	wsprintf(szBuf3, TEXT("실제위치 :%d"), m_Pos.x - CircusObject::m_sScreenPosX);
	TextOut(hdc, 200, 160, szBuf3, lstrlen(szBuf3));

	TCHAR szBuf4[128];
	wsprintf(szBuf4, TEXT("64? :%d"), CircusObject::m_sScreenPosX % 64);
	TextOut(hdc, 200, 180, szBuf4, lstrlen(szBuf4));

	if (m_eState == PL_DIE)
	{
		TCHAR szBuf[128];
		wsprintf(szBuf, TEXT("님뒤짐 ㅋ"));
		TextOut(hdc, 200, 200, szBuf, lstrlen(szBuf));
	}
}

void Player::Release()
{
	SAFE_DELETE(m_pBitMap);
}


bool Player::CollisionCheck(std::vector< CircusObject*>::iterator iter)
{
	RECT temp;
	RECT playerRect = { m_Pos.x, m_Pos.y, m_Pos.x + 64, m_Pos.y + 64 };

	if (IntersectRect(&temp, &(*iter)->GetCollisonBox(), &playerRect))
	{
		m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_DIE);
		m_eState = PL_DIE;
		return true;
	}

	return false;
}

void Player::ReStart()
{
	CircusObject::ReStart();
	m_Pos.x = CircusObject::m_sScreenPosX+70;
	m_Pos.y = 325;
	m_pBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_PLAYER_00);
	m_inputStartTime = 0;
	m_speed = CircusObject::m_sScreenSpeed;
	m_bOnAnimator = false;
	m_bJump = false;
	m_iMaxJumpCount = 70;
	m_iJumpConut = m_iMaxJumpCount;
	m_eState = PL_IDLE;
}