#include <Windows.h>

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //지역변수임 유지안됨 값
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT: //너의 작업영역이 지워졌으니까 빨리 다시그려라!
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15); 
		EndPaint(hWnd, &ps);
		return 0; //한동안은 페인트안에서 쓰자
	//case WM_LBUTTONDOWN:
	//	hdc = GetDC(hWnd);
	//	TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15); //모든그리기 함수는 DC의 핸들을 첫 번째 인수로 전달받아야함
	//	ReleaseDC(hWnd, hdc);
	//	return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//get release 세트
//beigin end 세트