#pragma once
#include <Windows.h>
#include <string>
#include <map>
using namespace std;

class Scene;
class SceneManager
{
private:
	map<string, Scene*> sceneContainer;
	Scene* currentScene;
	Scene* reservedScene;
public :
	void RegisterScene(const string& sceneName, Scene* scene);
	void ReserveChangeScene(const string& sceneName);
public :
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

public:
	SceneManager();
	~SceneManager();

};

