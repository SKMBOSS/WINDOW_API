#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Block;
class BitMap;
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
	void SaveData(string fileName);

private:
	MapEditor();
public:
	~MapEditor();
};

