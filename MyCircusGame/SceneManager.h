#pragma once
#include <Windows.h>
#include <map>

enum SCENE_STATE
{
	TITLE,
	STAGE_01
};

class Scene;
class SceneManager
{
private:
	static SceneManager* m_sThis;
	std::map<SCENE_STATE, Scene*> sceneContainer;
	SCENE_STATE currentSceneState;
private://이게맞나..
	HDC	m_hMemDC;
	HWND m_hWnd;
public:
	static SceneManager* GetInstance();
	inline Scene* GetCurrentScene()
	{
		return sceneContainer[currentSceneState];
	}
	void ChangeScene(SCENE_STATE state);
private:
	void InitSceneContainer();
public:
	void Init(HWND hWnd, HDC hdc);
	void Input(WPARAM wParam);
	void Update();
	void Draw(HDC hdc);
	void Release();
private:
	SceneManager();
public:
	~SceneManager();
};

