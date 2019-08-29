#pragma once
#include <Windows.h>
#include <map>

enum SCENE_STATE
{
	INTRO,
	MAIN_GAME
};

class Scene;
class SceneManager
{
private:
	static SceneManager* sceneManagerInstance;
	SceneManager();
	std::map<SCENE_STATE, Scene*> sceneContainer;
	SCENE_STATE currentSceneState;
private:
	void InitSceneContainer();
public:
	static SceneManager* GetInstance();
	inline Scene* GetCurrentScene() 
	{ 
		return sceneContainer[currentSceneState];
	}
	void ChangeScene(SCENE_STATE state);
public:
	void Init();
	void Input(WPARAM wParam);
	void Update();
	void Render(HDC hdc);
	void Release();

public:
	~SceneManager();

};

