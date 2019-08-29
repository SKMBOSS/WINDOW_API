#pragma once
#include <Windows.h>
class Scene
{
public :
	virtual void Init() = 0; 
	virtual void Input(WPARAM wParam) = 0;
	virtual void InputChar(WPARAM wParam) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
public:
	Scene();
	~Scene();
};

