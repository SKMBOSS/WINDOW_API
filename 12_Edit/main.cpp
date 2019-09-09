#include <Windows.h>
#define ID_EDIT 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyEdit");

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

HWND hEdit;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME OFN;
	char str[256];
	char lpastrfile[MAX_PATH] = "";
	


	//zeroMemory(&OFN, sizeof(OPENFILENAME)));
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.ini\0";
	OFN.lpstrFile = lpastrfile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("LOAD"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Me Two"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 50, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			if (GetSaveFileName(&OFN) != 0)
			{
				wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
				MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
			}
			MessageBox(hWnd, "First Button Clicked", "Button", MB_OK);
			break;
		case 1:
			MessageBox(hWnd, "Second Button Clicked", "Button", MB_OK);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


	/*HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[128];
	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL, 10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_EDIT:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128);
				SetWindowText(hWnd, str);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));*/

