#pragma once
#include "CircusObject.h"

class BackGround :
	public CircusObject
{
private:
	

public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	BackGround();
	virtual ~BackGround();
};

