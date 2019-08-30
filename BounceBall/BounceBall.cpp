#include <Windows.h>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BounceBall");

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
float GetDisTancePoint(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool isCrash(int r1, int r2, float dis)
{
	if (r1 + r2 > dis)
		return true;
	else
		return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100,100,1000,700 };
	static int x=200;
	static int y=200;
	static int speed_x = 5;
	static int speed_y = 5;
	int r = 50;

	static int x2 = 800;
	static int y2 = 500;
	static int speed_x2 = 5;
	static int speed_y2 = 5;
	int r2 = 30;

	switch (iMessage)
	{
	case WM_CREATE: //윈도우를 생성할 때 호출되는 메세지(초기화를 하기에 좋은 위치)
		SetTimer(hWnd, 1, 10, NULL); //타이머를 등록 1번타이머를 등록, 1000 = 밀리세컨드 = 1초, NULL = 함수포인터를 넣는데 통상 널
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE); //화면을 갱신하기위해

		x += speed_x;
		y += speed_y;

		x2 += speed_x2;
		y2 += speed_y2;

		if (x > rt.right-r)
		{
			speed_x = -5;
		}
		else if (x < rt.left+r)
		{
			speed_x = 5;
		}
		else if (y > rt.bottom-r)
		{
			speed_y = -5;
		}
		else if (y < rt.top+r)
		{
			speed_y = 5;
		}

		if (x2 > rt.right - r)
		{
			speed_x2 = -5;
		}
		else if (x2 < rt.left + r)
		{
			speed_x2 = 5;
		}
		else if (y2 > rt.bottom - r)
		{
			speed_y2 = -5;
		}
		else if (y2 < rt.top + r)
		{
			speed_y2 = 5;
		}

		if (isCrash(r, r2, GetDisTancePoint(x, y, x2, y2)))
		{
			//MessageBox(hWnd, TEXT("충돌"), TEXT("충돌"), MB_OK);
			KillTimer(hWnd, 1); // 셋햇으면 킬해야함
		}
		
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetPixel(hdc, 10, 10, RGB(0, 255, 0));
		Rectangle(hdc, rt.left,rt.top,rt.right,rt.bottom);
		Ellipse(hdc, x - r, y - r, x + r, y + r);
		Ellipse(hdc, x2 - r2, y2 - r2, x2 + r2, y2 + r2);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}