

#include <Windows.h>

#pragma comment (lib, "msimg32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DoubleBufferDraw");

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

HDC g_MemDc[3];
HBITMAP g_hBitMap[3];
HBITMAP g_hOld[3];
int x = 50;
int y = 50;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		//1. 백버퍼는 CreateCompatibleBitmap 으로 만든다
		//2. 다릉ㄴ 이미지는 백버퍼의 hdc를 기준으로 생각한다

		SetTimer(hWnd, 1, 10, NULL);
		hdc = GetDC(hWnd);
		g_MemDc[0] = CreateCompatibleDC(hdc);
		g_hBitMap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
		g_hOld[0] = (HBITMAP)SelectObject(g_MemDc[0], g_hBitMap[0]);

		g_MemDc[1] = CreateCompatibleDC(g_MemDc[0]);
		g_hBitMap[1] = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0 
			,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDc[1], g_hBitMap[1]);

		g_MemDc[2] = CreateCompatibleDC(g_MemDc[0]);
		g_hBitMap[2] = (HBITMAP)LoadImage(NULL, "char.bmp", IMAGE_BITMAP, 0, 0
			, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDc[2], g_hBitMap[2]);
		
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
		BitBlt(g_MemDc[0], 0, 0, 1024, 768, g_MemDc[1], 0, 0, SRCCOPY);

		//TransparentBlt(g_MemDc[0], 0, 0, 100, 100, g_MemDc[1], 0, 0, 240, 192, RGB(255, 0, 255));
		TransparentBlt(g_MemDc[0], x, y, 240, 192, g_MemDc[2], 0, 0, 100, 100, RGB(255, 0, 255));
		BitBlt(hdc, 0, 0, 1024, 768, g_MemDc[0], 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		//KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}