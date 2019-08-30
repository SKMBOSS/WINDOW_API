#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MatchCardGame");

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;

}

HDC hMemDC;
HBITMAP hBitMap;
HBITMAP hOLDBitMap;
int count = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		hdc = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hdc); //메모리DC를 잡아주는역할
		hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hOLDBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		if (count % 4 == 0)
			hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		else if (count % 4 == 1)
			hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		else if (count % 4 == 2)
			hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		else if (count % 4 == 3)
			hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		count++;

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		StretchBlt(hdc, 0, 0, 246, 320, hMemDC, 0, 0, 123, 160, SRCCOPY);
		//BitBlt(hdc, 500, 500, 500, 500, hMemDC, 0, 0, SRCCOPY);
		hOLDBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);
		SelectObject(hdc, hOLDBitMap);
		DeleteObject(hBitMap);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}