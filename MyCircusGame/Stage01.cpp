#include "Stage01.h"
#include "BitMap.h"
#include "ResourceManager.h"
#include "Macro.h"
#include "CircusObject.h"
#include "Player.h"
#include "BackGround.h"
#include "FireRing.h"
#include "Miter.h"

Stage01::Stage01()
{
}

Stage01::~Stage01()
{
}

void Stage01::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;
	
	for (int i = 0; i < 9; i++)
	{
		CircusObject* m_pBackGround = new BackGround();
		m_vecObj.push_back(m_pBackGround);
	}

	/*CircusObject* pFireRing = new FireRing();
	m_vecObj.push_back(pFireRing);*/

	CircusObject* pPlayer = new Player();
	m_vecObj.push_back(pPlayer);
	
	CircusObject* pMiter = new Miter();
	m_vecObj.push_back(pMiter);

	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
	{
		(*iter)->Init();
	}
}

void Stage01::Input(WPARAM wParam)
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
	{
		(*iter)->Input(wParam);
	}
}

void Stage01::TerminateInput(WPARAM wParam)
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
	{
		(*iter)->TerminateInput(wParam);
	}
}

void Stage01::Update()
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
	{
		(*iter)->Update();
	}
	InvalidateRect(m_hWnd, NULL, FALSE);
}

void Stage01::Draw(HDC hdc)
{
	for (auto iter = m_vecObj.begin(); iter != m_vecObj.end(); ++iter)
	{
		(*iter)->Draw(hdc);
	}
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