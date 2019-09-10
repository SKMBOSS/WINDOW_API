#include <Windows.h>
#include "MapEditor.h"
#include "Block.h"
#include <string>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("맵에디터");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 650, 600,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

HDC g_MemDC;
HBITMAP g_hBitMap;
HBITMAP g_hOld;


#define ID_R1 101
#define ID_R2 102
#define ID_R3 103
#define ID_R4 104
#define ID_R5 105
#define ID_R6 106
#define ID_R7 107
#define ID_R8 108
#define ID_R9 109
#define ID_R10 110
#define ID_R11 111
#define ID_R12 112
#define ID_R13 113

#define LOAD_BUTTON 0
#define SAVE_BUTTON 1

HWND r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13;

char messageStr[256];
char lpastrfile[MAX_PATH] = "";

//zeroMemory(&OFN, sizeof(OPENFILENAME)));

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT pt;

	OPENFILENAME OFN;
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
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 10, NULL);
		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitMap = CreateCompatibleBitmap(hdc, 13 * 32, 13 * 32);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitMap);
		MapEditor::GetInstance()->Init(hWnd, g_MemDC);
		ReleaseDC(hWnd, g_MemDC);
		ReleaseDC(hWnd, hdc);

		CreateWindow("button", "벽돌", WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 500, 5, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);

		r1 = CreateWindow("button", "전체", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 25, 50, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);

		r2 = CreateWindow("button", "상", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 55, 50, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);
		r3 = CreateWindow("button", "하", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			555, 55, 50, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL);
		r4 = CreateWindow("button", "좌", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 85, 50, 30, hWnd, (HMENU)ID_R4, g_hInst, NULL);
		r5 = CreateWindow("button", "우", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			555, 85, 50, 30, hWnd, (HMENU)ID_R5, g_hInst, NULL);

		CreateWindow("button", "강철", WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 500, 5+150, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);

		r6 = CreateWindow("button", "전체", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 25+ 150, 50, 30, hWnd, (HMENU)ID_R6, g_hInst, NULL);

		r7 = CreateWindow("button", "상", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 55+ 150, 50, 30, hWnd, (HMENU)ID_R7, g_hInst, NULL);

		r8 = CreateWindow("button", "하", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			555, 55+ 150, 50, 30, hWnd, (HMENU)ID_R8, g_hInst, NULL);

		r9 = CreateWindow("button", "좌", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 85+ 150, 50, 30, hWnd, (HMENU)ID_R9, g_hInst, NULL);

		r10 = CreateWindow("button", "우", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			555, 85+ 150, 50, 30, hWnd, (HMENU)ID_R10, g_hInst, NULL);

		CreateWindow("button", "특수", WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 500, 5 + 300, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);

		r11 = CreateWindow("button", "얼음", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 25 + 300, 50, 30, hWnd, (HMENU)ID_R11, g_hInst, NULL);

		r12 = CreateWindow("button", "덤불", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 55 + 300, 50, 30, hWnd, (HMENU)ID_R12, g_hInst, NULL);

		r13 = CreateWindow("button", "바다", WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			505, 55 + 300+30, 50, 30, hWnd, (HMENU)ID_R13, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("LOAD"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			23, 32 * 13 + 20+20, 100, 30, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("SAVE"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20+10*32-5, 32 * 13 + 20 + 20, 100, 30, hWnd, (HMENU)1, g_hInst, NULL);

		SendMessage(r1, BM_SETCHECK, BST_CHECKED, 0);
		return 0;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (LOWORD(wParam))
			{
			case ID_R1:
				Block::m_SelectBlockType= BLOCK_NORMAL_FULL;
				break;
			case ID_R2:
				Block::m_SelectBlockType = BLOCK_NORMAL_TOP;
				break;
			case ID_R3:
				Block::m_SelectBlockType = BLOCK_NORMAL_BOT;
				break;
			case ID_R4:
				Block::m_SelectBlockType = BLOCK_NORMAL_LEFT;
				break;
			case ID_R5:
				Block::m_SelectBlockType = BLOCK_NORMAL_RIGHT;
				break;
			case ID_R6:
				Block::m_SelectBlockType = BLOCK_METAL_FULL;
				break;
			case ID_R7:
				Block::m_SelectBlockType = BLOCK_METAL_TOP;
				break;
			case ID_R8:
				Block::m_SelectBlockType = BLOCK_METAL_BOT;
				break;
			case ID_R9:
				Block::m_SelectBlockType = BLOCK_METAL_LEFT;
				break;
			case ID_R10:
				Block::m_SelectBlockType = BLOCK_METAL_RIGHT;
				break;
			case ID_R11:
				Block::m_SelectBlockType = BLOCK_ICE;
				break;
			case ID_R12:
				Block::m_SelectBlockType = BLOCK_FOREST;
				break;
			case ID_R13:
				Block::m_SelectBlockType = BLOCK_WATER;
				break;
			case LOAD_BUTTON:
				if (GetSaveFileName(&OFN) != 0)
				{
					wsprintf(messageStr, "%s 파일을 선택했습니다.", OFN.lpstrFile);
					MessageBox(hWnd, messageStr, "파일 저장 성공", MB_OK);

					MapEditor::GetInstance()->LoadData(OFN.lpstrFile);
					
				}
				break;
			case SAVE_BUTTON:
				if (GetSaveFileName(&OFN) != 0)
				{
					wsprintf(messageStr, "%s 파일을 선택했습니다.", OFN.lpstrFile);
					MessageBox(hWnd, messageStr, "파일 선택 성공", MB_OK);

					MapEditor::GetInstance()->SaveData(OFN.lpstrFile);
				}
				break;
			}
		}
		return 0;
	case WM_TIMER:
		MapEditor::GetInstance()->Update();
		return 0;
	case WM_LBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		MapEditor::GetInstance()->Input(pt);
		return 0;
	case WM_RBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		MapEditor::GetInstance()->InputR(pt);
		return 0;
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MapEditor::GetInstance()->Draw(g_MemDC);
		BitBlt(hdc, 0+20, 0+20, 13*32+20, 13*32+20, g_MemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}