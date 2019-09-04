#include <Windows.h>
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

HDC g_MemDc;
HBITMAP g_hBitMap;
HBITMAP g_hOld;
int x = 50;
int y = 50;
BitMap* back = new BitMap;
BitMap* back2 = new BitMap;
BitMap* player = new BitMap;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		hdc = GetDC(hWnd);
		g_MemDc = CreateCompatibleDC(hdc);
		g_hBitMap = CreateCompatibleBitmap(hdc, 512, 450);
		g_hOld = (HBITMAP)SelectObject(g_MemDc, g_hBitMap);

		back->Init(g_MemDc, "Resource\\Circus\\back.bmp");
		back2->Init(g_MemDc, "Resource\\Circus\\back.bmp");
		player->Init(g_MemDc, "Resource\\Circus\\win.bmp");

		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		back->TransDraw(g_MemDc, 0, 0);
		back2->TransDraw(g_MemDc, 0, 180);
		player->TransDraw(g_MemDc, x, y);

		BitBlt(hdc, 0, 0, 512, 450, g_MemDc, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		delete player;
		delete back;
		delete back2;
		//KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}