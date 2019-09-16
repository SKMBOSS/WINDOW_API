#include "SceneManager.h"
#include "Scene.h"
#include "Stage.h"
#include "Macro.h"
using namespace std;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::m_sThis = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (m_sThis == nullptr)
	{
		m_sThis = new SceneManager;
	}
	return m_sThis;
}

void SceneManager::InitSceneContainer()
{
	//sceneContainer.insert(make_pair(SCENE_STATE::INTRO, new Intro));
	sceneContainer.insert(make_pair(SCENE_STATE::STAGE, new Stage));
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
	currentSceneState = SCENE_STATE::STAGE;
	GetCurrentScene()->Init();
}

void SceneManager::Update(float fElapseTime)
{
	GetCurrentScene()->Update(fElapseTime);
}

void SceneManager::Render(HDC hdc)
{
	GetCurrentScene()->Render(hdc);
}

void SceneManager::Release()
{
	GetCurrentScene()->Release();

	for (auto iter = sceneContainer.begin(); iter != sceneContainer.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	sceneContainer.clear();
	SAFE_DELETE(m_sThis);
}