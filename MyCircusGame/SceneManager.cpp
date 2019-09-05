#include "SceneManager.h"
#include "Scene.h"
#include "Stage01.h"
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
	sceneContainer.insert(make_pair(SCENE_STATE::STAGE_01, new Stage01));
}

void SceneManager::ChangeScene(SCENE_STATE state)
{
	if (currentSceneState == state)
		return;

	GetCurrentScene()->Release();
	currentSceneState = state;
	GetCurrentScene()->Init(m_hWnd, m_hMemDC);
}

void SceneManager::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;
	m_hMemDC = hdc;
	InitSceneContainer();
	currentSceneState = SCENE_STATE::STAGE_01;
	GetCurrentScene()->Init(m_hWnd, m_hMemDC);
}

void SceneManager::Input(WPARAM wParam)
{
	GetCurrentScene()->Input(wParam);
}

void SceneManager::TerminateInput(WPARAM wParam)
{
	GetCurrentScene()->TerminateInput(wParam);
}

void SceneManager::Update()
{
	GetCurrentScene()->Update();
}

void SceneManager::Draw(HDC hdc)
{
	GetCurrentScene()->Draw(hdc);
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