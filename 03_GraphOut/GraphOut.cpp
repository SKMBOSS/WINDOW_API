#include <Windows.h>
#include <vector>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");

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
#define PI 3.141592f
float DegreeToRadian(float _degree)
{
	return (PI / 180) * _degree;
}

void DrwawCircle(HDC hdc, int x, int y, int xR, int yR)
{
	int i = 0;

	for (int i = 0; i < 360; i++)
	{
		int _x = xR * cosf(DegreeToRadian(i)) + x;
		int _y = yR * sinf(DegreeToRadian(i)) + y;

		SetPixel(hdc, _x, _y, RGB(255, 0, 0));
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //지역변수임 유지안됨 값
	PAINTSTRUCT ps;
	RECT rt = { 100,100,400,300 };

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetPixel(hdc, 10, 10, RGB(0, 255, 0));

		int x = 200;
		int y = 200;
		int r = 100;

		//실습
		DrwawCircle(hdc, 400, 200, 50, 80);

		Rectangle(hdc, x - r, y - r, x + r, y + r);
		Ellipse(hdc, x - r, y - r, x + r, y + r);

		MoveToEx(hdc, x, y - r, NULL);
		LineTo(hdc, x - r, y);
		MoveToEx(hdc, x - r, y, NULL);
		LineTo(hdc, x, y + r);
		MoveToEx(hdc, x, y + r, NULL);
		LineTo(hdc, x + r, y);
		MoveToEx(hdc, x + r, y, NULL);
		LineTo(hdc, x, y - r);

		EndPaint(hWnd, &ps);
		return 0; //한동안은 페인트안에서 쓰자

	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}