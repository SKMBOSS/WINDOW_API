#include "Stage01.h"
#include "BitMap.h"

Stage01::Stage01()
{
}

Stage01::~Stage01()
{
}

void Stage01::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;

	back = new BitMap();
	back2 = new BitMap();
	player = new BitMap();

	back->Init(hdc, "Resource\\Circus\\back.bmp");
	back2->Init(hdc, "Resource\\Circus\\back.bmp");
	player->Init(hdc, "Resource\\Circus\\win.bmp");

	x = 50;
	y = 50;
}

void Stage01::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		x -= 8;
		break;
	case VK_RIGHT:
		x += 8;
		break;
	case VK_UP:
		y -= 8;
		break;
	case VK_DOWN:
		y += 8;
		break;
	}
}

void Stage01::Update()
{
	InvalidateRect(m_hWnd, NULL, FALSE);
}

void Stage01::Draw(HDC hdc)
{
	back->Draw(hdc, 0, 0);
	back2->Draw(hdc, 0, 180);
	player->Draw(hdc, x, y);
}

void Stage01::Release()
{
	delete back;
	delete back2;
	delete player;
}