#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

class Block;
class MapEditor
{
private:
	static MapEditor* m_sThis;
public:
	static MapEditor* GetInstance();
private:
	HWND			m_hWnd;
	vector<Block*>  m_vecBlock;
public:
	void Init(HWND hWnd, HDC hdc);
	void Input(POINT pt);
	void InputR(POINT pt);
	void Update();
	void Draw(HDC hdc);
	void Release();
private:
	MapEditor();
public:
	~MapEditor();
};

