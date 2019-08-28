#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst; //�ν��Ͻ��� �ڵ�
LPCTSTR lpszClass = TEXT("KeyDown"); //�̸����뵵�� Ŭ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;		//������ �ڵ�(�������)
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
	HDC hdc; //���������� �����ȵ� ��
	PAINTSTRUCT ps;
	static int x = 100; // ��ǥ���� �����ؾ��ϹǷ� ����ƽ
	static int y = 100;
	int len;

	switch (iMessage)
	{
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
			y-= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
	InvalidateRect(hWnd, NULL, TRUE);
	return 0;
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, x, y, TEXT("A"),1);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}