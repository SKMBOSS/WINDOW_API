#include "GameFrameWork.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <math.h>
#include <stdio.h>

GameFrameWork::GameFrameWork()
{
	m_LastTime = std::chrono::system_clock::now();
}

GameFrameWork::~GameFrameWork()
{
}

void GameFrameWork::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	HDC hdc = GetDC(hWnd);
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, 1024, 768);
	m_hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	ResourceManager::GetInstance()->Init(hdc);
	SceneManager::GetInstance()->Init(hWnd, hdc);
	ReleaseDC(hWnd, hdc);
}

void GameFrameWork::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	SceneManager::GetInstance()->Update(m_fElapseTime);
}

void GameFrameWork::Render()
{
	HDC hdc = GetDC(m_hWnd);
	SceneManager::GetInstance()->Render(m_hMemDC);
	BitBlt(hdc, 0, 0, 1024, 768, m_hMemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameFrameWork::Release()
{
	SelectObject(m_hMemDC, m_hOld);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}