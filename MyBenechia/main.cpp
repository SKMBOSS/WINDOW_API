#include "MyBenechia.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyBenechia");

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
		100, 100, 640, 480,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	MyBenechia *mainGame;
	mainGame = MyBenechia::GetInstance();

	HDC hdc;
	PAINTSTRUCT ps;

	mainGame->Init();
	switch (iMessage)
	{
	case WM_CREATE: //윈도우를 생성할 때 호출되는 메세지(초기화를 하기에 좋은 위치)
		SetTimer(hWnd, 1, 10, NULL);
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE); //화면을 갱신하기위해
		//mainGame->Update();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BeginPaint(hWnd, &ps);
		mainGame->Render(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		//mainGame->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}