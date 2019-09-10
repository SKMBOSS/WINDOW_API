#include "MapEditor.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include "Block.h"
#include "Macro.h"


MapEditor* MapEditor::m_sThis = nullptr;

MapEditor::MapEditor()
{
}

MapEditor::~MapEditor()
{
}

MapEditor* MapEditor::GetInstance()
{
	if (m_sThis == nullptr)
		m_sThis = new MapEditor();

	return m_sThis;
}

void MapEditor::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;
	ResourceManager::GetInstance()->Init(hdc);
	
	for (int i = 0; i < 13 * 17; i++)
	{
		Block* block = new Block();
		m_vecBlock.push_back(block);
	}
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); ++iter)
		(*iter)->Init();
}

void MapEditor::Input(POINT pt)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); ++iter)
		(*iter)->Input(pt);
}

void MapEditor::InputR(POINT pt)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); ++iter)
		(*iter)->InputR(pt);
}

void MapEditor::Update()
{
	RECT rt = { 0 + 20, 0 + 20, 13 * 32 + 20, 17 * 32 + 20 };
	InvalidateRect(m_hWnd, &rt, FALSE);
}

void MapEditor::Draw(HDC hdc)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); ++iter)
		(*iter)->Draw(hdc);
}

void MapEditor::Release()
{
	ResourceManager::GetInstance()->Release();
	//SceneManager::GetInstance()->Release();
	SAFE_DELETE(m_sThis);
}

void MapEditor::SaveData(string fileName)
{
	//
}