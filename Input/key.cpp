//#include <Windows.h>
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HINSTANCE g_hInst; //�ν��Ͻ��� �ڵ�
//LPCTSTR lpszClass = TEXT("KeyDown"); //�̸����뵵�� Ŭ����
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
//{
//	HWND hWnd;		//������ �ڵ�(�������)
//	MSG Message;
//	WNDCLASS WndClass;
//	g_hInst = hInstance;
//
//	WndClass.cbClsExtra = 0;		//ī��Ʈ����Ʈ Ŭ���� ����Ʈ�� ��� 0�����
//	WndClass.cbWndExtra = 0;		//��ΰ��� �׻� 0���� �����ض�
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//�����ϸ� �Ͼ��� -> �̻����� �ٲ��ִ¾� 
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);						//Ŀ�����
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					//�̸���������
//	WndClass.hInstance = hInstance;
//	WndClass.lpfnWndProc = WndProc;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.lpszMenuName = NULL;
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;							//âũ�� �������� �׸��ų� �ȱ׸��ų� �׸��� �����ض�
//	RegisterClass(&WndClass);											//�̷��� �����Ѱ� ����Ѵ�
//
//	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,		//������ ������������ ���� 
//		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		//����Ʈ�� ����ٶ��;
//		NULL, (HMENU)NULL, hInstance, NULL);
//	ShowWindow(hWnd, nCmdShow);
//
//	while (GetMessage(&Message, NULL, 0, 0))							//���Ⱑ ���� �߿�
//	{
//		TranslateMessage(&Message);
//		DispatchMessage(&Message);										//����ġ�ؼ� �ݹ�θ��°�
//	}
//	return (int)Message.wParam;
//
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc; //���������� �����ȵ� ��
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