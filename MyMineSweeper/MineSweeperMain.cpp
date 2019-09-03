#include <windows.h>
#include "MainGame.h"
#include "GameManager.h"
#include "resource.h"
#include <crtdbg.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SettingDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam); //새콜백 선언
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyMineSweeper");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(160);

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // 메뉴 연동
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
	HDC hdc;
	PAINTSTRUCT ps;
	POINT pt;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 100, NULL);
		MainGame::GetInstance()->Init(hWnd, hdc);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_TIMER:
		//InvalidateRect(hWnd, NULL, TRUE);
		MainGame::GetInstance()->Update();
		return 0;
	case WM_LBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		MainGame::GetInstance()->LBInput(pt);
		return 0;
	case WM_RBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		MainGame::GetInstance()->RbInput(pt);
		return 0;
	case WM_COMMAND: //메뉴바만
		switch (LOWORD(wParam))
		{
		case ID_FILE_SETTING:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1)
				, hWnd, SettingDlg);
			InvalidateRect(hWnd, NULL, true);
			break;
		}
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MainGame::GetInstance()->Draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		MainGame::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

INT_PTR CALLBACK SettingDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hRadio;
	switch (message)
	{
	case WM_INITDIALOG: // 처음난이도 설정한거고
		hRadio = GetDlgItem(hDlg, IDC_RADIO1);
		SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) //얘가확인
		{
			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
				GameManager::GetInstance()->SetGameMode(GAME_MODE_EASY);
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
				GameManager::GetInstance()->SetGameMode(GAME_MODE_NOMAL);
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
				GameManager::GetInstance()->SetGameMode(GAME_MODE_HARD);
		
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}

	return (INT_PTR)FALSE;
}