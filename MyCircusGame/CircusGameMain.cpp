#include <Windows.h>
#include "CircusGame.h"
#include "BitMap.h"

//#pragma comment (lib, "msimg32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("서커스게임_이정수");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	RECT rt = { 0,0,512,450 };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		700, 200, rt.right-rt.left, rt.bottom-rt.top,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;

}

HDC g_MemDC;
HBITMAP g_hBitMap;
HBITMAP g_hOld;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 10, NULL);
		/****************더블버퍼********************/
		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitMap = CreateCompatibleBitmap(hdc, 512, 450);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitMap);
		/****************************************************/
		CircusGame::GetInstance()->Init(hWnd, g_MemDC);
		ReleaseDC(hWnd, g_MemDC);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_TIMER:
		CircusGame::GetInstance()->Update();
		return 0;
	case WM_KEYDOWN:
		CircusGame::GetInstance()->Input(wParam);
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		CircusGame::GetInstance()->Draw(g_MemDC);
		BitBlt(hdc, 0, 0, 512, 450, g_MemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}