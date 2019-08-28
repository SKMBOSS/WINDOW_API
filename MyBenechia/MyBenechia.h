#pragma once
#include <Windows.h>
#include "TextBrick.h"

class MyBenechia
{
private:
	static MyBenechia* MyBenechiaInstance;
	RECT rt = { 50,50,200,300 };
	TextBrick *tb;
public:
	static MyBenechia* GetInstance();

	void Init();
	void Update();
	void Render(HDC _hdc);
	void Release();

	MyBenechia();
	~MyBenechia();
};

