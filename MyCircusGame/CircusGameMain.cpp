#include <Windows.h>
#include "BitMap.h"

//#pragma comment (lib, "msimg32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("��Ŀ������_������");

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

HDC g_MemDc[3];
HBITMAP g_hBitMap[3];
HBITMAP g_hOld[3];
int x = 50;
int y = 50;
BitMap* back = new BitMap;
BitMap* player = new BitMap;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		//1. ����۴� CreateCompatibleBitmap ���� �����
		//2. �ٸ� �̹����� ������� hdc�� �������� �����Ѵ�

		SetTimer(hWnd, 1, 10, NULL);
		hdc = GetDC(hWnd);
		g_MemDc[0] = CreateCompatibleDC(hdc);
		g_hBitMap[0] = CreateCompatibleBitmap(hdc, 512, 450);
		g_hOld[0] = (HBITMAP)SelectObject(g_MemDc[0], g_hBitMap[0]);

		
		back->Init(g_MemDc[0], "Resource\\Circus\\back.bmp");
		player->Init(g_MemDc[0], "Resource\\Circus\\win.bmp");
		/*g_MemDc[1] = CreateCompatibleDC(g_MemDc[0]);
		g_hBitMap[1] = (HBITMAP)LoadImage(NULL, "Resource\\Circus\\back.bmp", IMAGE_BITMAP, 0, 0
			, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDc[1], g_hBitMap[1]);

		g_MemDc[2] = CreateCompatibleDC(g_MemDc[0]);
		g_hBitMap[2] = (HBITMAP)LoadImage(NULL, "Resource\\Circus\\win.bmp", IMAGE_BITMAP, 0, 0
			, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDc[2], g_hBitMap[2]);*/

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

		back->Draw(g_MemDc[0], 0, 0);
		player->TransDraw(g_MemDc[0], x, y);

		BitBlt(hdc, 0, 180, 512, 270, g_MemDc[0], 0, 0, SRCCOPY);
		//BitBlt(g_MemDc[0], 0, 0, 512, 450, g_MemDc[1], 0, 0, SRCCOPY);
		

		////TransparentBlt(g_MemDc[0], 0, 0, 100, 100, g_MemDc[1], 0, 0, 240, 192, RGB(255, 0, 255));
		//TransparentBlt(g_MemDc[0], x, y, 76, 75, g_MemDc[2], 0, 0, 76, 75, RGB(255, 0, 255));
		//BitBlt(hdc, 0, 180, 512, 270, g_MemDc[0], 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		delete player;
		delete back;
		//KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}