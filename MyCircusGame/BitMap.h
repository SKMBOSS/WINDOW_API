#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class BitMap
{
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldBitMap;
	SIZE		m_size;
public:
	inline SIZE GetSize()
	{
		return m_size;
	}
public:
	void Init(HDC hdc, string path);
	void Draw(HDC hdc, POINT pos);

	void Release();
public:
	BitMap();
	~BitMap();
};

