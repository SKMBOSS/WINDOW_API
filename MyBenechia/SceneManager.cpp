#include "SceneManager.h"
#include "Scene.h"
#include "Intro.h"
#include "MainGame.h"
using namespace std;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (sceneManagerInstance == nullptr)
	{
		sceneManagerInstance = new SceneManager;
	}
	return sceneManagerInstance;
}

void SceneManager::InitSceneContainer()
{
	sceneContainer.insert(make_pair(SCENE_STATE::INTRO, new Intro));
	sceneContainer.insert(make_pair(SCENE_STATE::MAIN_GAME, new MainGame));
}

void SceneManager::ChangeScene(SCENE_STATE state)
{
	if (currentSceneState == state)
		return;

	GetCurrentScene()->Release();
	currentSceneState = state;
	GetCurrentScene()->Init();
}

void SceneManager::Init()
{
	InitSceneContainer();
	currentSceneState = SCENE_STATE::INTRO;
	GetCurrentScene()->Init();
}

void SceneManager::Input(WPARAM wParam)
{
	GetCurrentScene()->Input(wParam);
}

void SceneManager::Update()
{
	GetCurrentScene()->Update();
}

void SceneManager::Render(HDC hdc)
{
	GetCurrentScene()->Render(hdc);
}

void SceneManager::Release()
{
	GetCurrentScene()->Release();

	for (auto it = sceneContainer.begin(); it != sceneContainer.end(); it++)
		delete it->second;

	sceneContainer.clear();
}

