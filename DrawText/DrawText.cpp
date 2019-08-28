#include <Windows.h>
#include <vector>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst; //인스턴스의 핸들
LPCTSTR lpszClass = TEXT("TextOut"); //이름쓸용도의 클래스

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;		//윈도우 핸들(몇번인지)
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;		//카운트바이트 클리어 엑스트라 통상 0쓰면됨
	WndClass.cbWndExtra = 0;		//요두개는 항상 0쓴다 생각해라
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//시작하면 하얀배경 -> 이색깔을 바꿔주는애 
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);						//커서모양
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					//이름옆아이콘
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;							//창크기 변했을때 그릴거냐 안그릴거냐 그리면 어케해라
	RegisterClass(&WndClass);											//이렇게 설정한거 등록한다

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,		//보통은 오버랩윈도우 ㅇㅇ 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		//디폴트로 대충다띄움;
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))							//여기가 제일 중요
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);										//디스패치해서 콜백부르는거
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
		return 0; //한동안은 페인트안에서 쓰자
	
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}