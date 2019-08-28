#include <Windows.h>
#include <vector>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //지역변수임 유지안됨 값
	PAINTSTRUCT ps;
	RECT rt = { 100,100,400,300 }; // DrawText() 설치할 사각형 좌표  (left,top) (right, bottom)
	LPCTSTR str = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을 "
		"깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
		"황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끌이 되어 한숨의 미풍에 "
		"날아갔습니다.");
	//프로젝트설정 하기 싫어서 이렇게함
	//LPCTSTR 얘가 포인터고 못찾으면 auto로 찾자

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0; //한동안은 페인트안에서 쓰자

	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//67p