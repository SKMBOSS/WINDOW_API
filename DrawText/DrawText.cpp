#include <Windows.h>
#include <vector>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst; //�ν��Ͻ��� �ڵ�
LPCTSTR lpszClass = TEXT("TextOut"); //�̸����뵵�� Ŭ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;		//������ �ڵ�(�������)
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;		//ī��Ʈ����Ʈ Ŭ���� ����Ʈ�� ��� 0�����
	WndClass.cbWndExtra = 0;		//��ΰ��� �׻� 0���� �����ض�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//�����ϸ� �Ͼ��� -> �̻����� �ٲ��ִ¾� 
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);						//Ŀ�����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					//�̸���������
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;							//âũ�� �������� �׸��ų� �ȱ׸��ų� �׸��� �����ض�
	RegisterClass(&WndClass);											//�̷��� �����Ѱ� ����Ѵ�

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,		//������ ������������ ���� 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		//����Ʈ�� ����ٶ��;
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))							//���Ⱑ ���� �߿�
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);										//����ġ�ؼ� �ݹ�θ��°�
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
		int _x = xR * cosf(DegreeToRadian(i))+ x;
		int _y = yR * sinf(DegreeToRadian(i)) + y;

		SetPixel(hdc, _x, _y, RGB(255, 0, 0));
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //���������� �����ȵ� ��
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

		DrwawCircle(hdc,400, 200, 50, 80);

		Rectangle(hdc, x-r, y-r, x+r, y+r);
		Ellipse(hdc, x - r, y - r, x + r, y + r);

		MoveToEx(hdc, x, y - r, NULL);
		LineTo(hdc, x - r, y);
		MoveToEx(hdc, x - r, y, NULL);
		LineTo(hdc, x, y + r);
		MoveToEx(hdc, x, y + r, NULL);
		LineTo(hdc, x + r, y);
		MoveToEx(hdc, x + r, y, NULL);
		LineTo(hdc, x, y - r);

		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0; //�ѵ����� ����Ʈ�ȿ��� ����
	
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}