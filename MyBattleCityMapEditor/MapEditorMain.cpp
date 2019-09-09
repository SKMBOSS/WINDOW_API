#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include "BitMap.h"

using namespace std;

#define ID_EDIT 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BattleCityMapEditor");

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
ifstream inFile;
vector<BitMap*> vecBoard;
string filename = "왜안돼";
string szBUF = "";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	OPENFILENAME OFN;
	char str[256];
	char lpastrfile[MAX_PATH] = "";
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.ini\0";
	OFN.lpstrFile = lpastrfile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";

	TCHAR szBuf[128];
	
	wsprintf(szBuf, TEXT("님뒤짐 ㅋ"));

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 10, NULL);

		CreateWindow(TEXT("button"), TEXT("LOAD"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Me Two"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 50, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			if (GetSaveFileName(&OFN) != 0)
			{
				filename = OFN.lpstrFile;
				wsprintf(str, "%s", OFN.lpstrFile);
				MessageBox(hWnd, filename.c_str(), "파일 열기 성공", MB_OK);
				
				inFile.open(filename);


			}
			break;
		case 1:
			if (GetSaveFileName(&OFN) != 0)
			{
				wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
				MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
			}
			MessageBox(hWnd, "Second Button Clicked", "Button", MB_OK);
			break;
		}
		return 0;
	case WM_TIMER:
		if (!inFile.eof())
		{
			inFile >> szBUF;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BeginPaint(hWnd, &ps);
		
	
		TextOut(hdc, 200, 200, szBuf, lstrlen(szBuf));
		TextOut(hdc, 200, 300, filename.c_str(), filename.length());
		TextOut(hdc, 200, 400, szBUF.c_str(), szBUF.length());

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
