#pragma once
#include <Windows.h>
#include <map>

enum SCENE_STATE
{
	TITLE,
	STAGE
};

class Scene;
class SceneManager
{
private:
	static SceneManager* m_sThis;
	std::map<SCENE_STATE, Scene*> sceneContainer;
	SCENE_STATE currentSceneState;
private:
	HDC		m_hMemDC;
	HWND	m_hWnd;
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
	void Init();
	void Update(float fElapseTime);
	void Render();
	void Release();
private:
	SceneManager();
public:
	~SceneManager();
};

