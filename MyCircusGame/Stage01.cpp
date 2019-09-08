#include "Stage01.h"
#include "BitMap.h"
#include "ResourceManager.h"
#include "Macro.h"
#include "CircusObject.h"
#include "Player.h"
#include "BackGround.h"
#include "FireRing.h"
#include "FireJar.h"
#include "Miter.h"
#include "time.h"

Stage01::Stage01()
{
}

Stage01::~Stage01()
{
}

void Stage01::Init(HWND hWnd, HDC hdc)
{
	srand(GetTickCount());
	m_hWnd = hWnd;
	m_eState = STAGE01_PLAYING;
	m_bWaiting = false;
	m_DeathTime = 44444;

	for (int i = 0; i < 110; i++)
	{
		CircusObject* m_pBackGround = new BackGround();
		m_vecObj.push_back(m_pBackGround);
	}

	m_FireStartIter = m_vecObj.end();
	for (int i = 0; i < 3; i++)
	{
		CircusObject* pFireRing = new FireRing();
		m_vecObj.push_back(pFireRing);
	}

	for (int i = 0; i < 6; i++)
	{
		CircusObject* pFireJar = new FireJar();
		m_vecObj.push_back(pFireJar);
	}

	m_PlayerIter = m_vecObj.end();
	CircusObject* pPlayer = new Player();
	m_vecObj.push_back(pPlayer);

	CircusObject* pMiter = new Miter();
	m_vecObj.push_back(pMiter);

	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
		(*iter)->Init();
}

void Stage01::Input(WPARAM wParam)
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
		(*iter)->Input(wParam);
}

void Stage01::TerminateInput(WPARAM wParam)
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
		(*iter)->TerminateInput(wParam);
}

void Stage01::Update()
{
	if (m_eState == STAGE01_PLAYING && !m_bWaiting)
	{
		for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
			(*iter)->Update();

		for (auto iter = m_FireStartIter; iter != m_PlayerIter; ++iter)
		{
			if ((*m_PlayerIter)->CollisionCheck(iter))
			{
				m_DeathTime = GetTickCount();
				m_pScreenBitMap = ResourceManager::GetInstance()->GetBitMap(RES_TYPE_WAITING_SCENE);
				m_bWaiting = true;
			}
		}
	}

	if (GetTickCount() - m_DeathTime >= 2000 && m_bWaiting)
	{
		m_eState = STAGE01_WATING;
		m_bWaiting = false;
		m_DeathTime = GetTickCount();
	}

	if (GetTickCount() - m_DeathTime >= 2000 && m_eState == STAGE01_WATING)
	{
		(*m_PlayerIter)->ReStart();
		for (auto iter = m_FireStartIter; iter != m_PlayerIter; ++iter)
			(*iter)->ReStart();

		m_eState = STAGE01_PLAYING;
	}
	InvalidateRect(m_hWnd, NULL, FALSE);
}

void Stage01::Draw(HDC hdc)
{

	if (m_eState == STAGE01_PLAYING)
	{
		for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
			(*iter)->Draw(hdc);
	}
	else if (m_eState == STAGE01_WATING)
		m_pScreenBitMap->Draw(hdc, 0, 0);
}

void Stage01::Release()
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); iter++)
	{
		SAFE_RELEASE(*iter);
		SAFE_DELETE(*iter);
	}
	m_vecObj.clear();
}