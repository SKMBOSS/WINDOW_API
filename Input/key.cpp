//#include <Windows.h>
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HINSTANCE g_hInst; //인스턴스의 핸들
//LPCTSTR lpszClass = TEXT("KeyDown"); //이름쓸용도의 클래스
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
//{
//	HWND hWnd;		//윈도우 핸들(몇번인지)
//	MSG Message;
//	WNDCLASS WndClass;
//	g_hInst = hInstance;
//
//	WndClass.cbClsExtra = 0;		//카운트바이트 클리어 엑스트라 통상 0쓰면됨
//	WndClass.cbWndExtra = 0;		//요두개는 항상 0쓴다 생각해라
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//시작하면 하얀배경 -> 이색깔을 바꿔주는애 
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);						//커서모양
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					//이름옆아이콘
//	WndClass.hInstance = hInstance;
//	WndClass.lpfnWndProc = WndProc;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.lpszMenuName = NULL;
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;							//창크기 변했을때 그릴거냐 안그릴거냐 그리면 어케해라
//	RegisterClass(&WndClass);											//이렇게 설정한거 등록한다
//
//	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,		//보통은 오버랩윈도우 ㅇㅇ 
//		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		//디폴트로 대충다띄움;
//		NULL, (HMENU)NULL, hInstance, NULL);
//	ShowWindow(hWnd, nCmdShow);
//
//	while (GetMessage(&Message, NULL, 0, 0))							//여기가 제일 중요
//	{
//		TranslateMessage(&Message);
//		DispatchMessage(&Message);										//디스패치해서 콜백부르는거
//	}
//	return (int)Message.wParam;
//
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc; //지역변수임 유지안됨 값
//	PAINTSTRUCT ps;
//	static int x = 100;
//	static int y = 100;
//	int len;
//
//	switch (iMessage)
//	{
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_LEFT:
//			x -= 8;
//			break;
//		case VK_RIGHT:
//			x += 8;
//			break;
//		case VK_UP:
//			y-= 8;
//			break;
//		case VK_DOWN:
//			y += 8;
//			break;
//		}
//	InvalidateRect(hWnd, NULL, TRUE);
//	return 0;
//	
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		TextOut(hdc, x, y, TEXT("A"),1);
//		EndPaint(hWnd, &ps);
//		return 0;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//
//	}
//
//	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
//}