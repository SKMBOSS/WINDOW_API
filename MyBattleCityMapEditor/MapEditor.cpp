#include "MapEditor.h"
#include "ResourceManager.h"
#include "BitMap.h"
#include "Block.h"
#include "Macro.h"
#include <fstream>
#include <iostream>


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

	for (int i = 0; i < 13 * 13; i++)
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
	RECT rt = { 0 + 20, 0 + 20, 13 * 32 + 20, 13 * 32 + 20 };
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

	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	m_vecBlock.clear();
	SAFE_DELETE(m_sThis);
}

void MapEditor::LoadData(string fileName)
{
	auto iter = m_vecBlock.begin();
	int temp;
	// read File
	ifstream openFile(fileName);
	if (openFile.is_open()) 
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				openFile >> temp;
				(*iter)->SetBitMap(temp);
				iter++;
			}
		}
		openFile.close();
	}

}

void MapEditor::SaveData(string fileName)
{
	// write File
	ofstream writeFile(fileName);
	if (writeFile.is_open())
	{
		auto iter = m_vecBlock.begin();

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				writeFile << (*iter)->GetType() << " ";
				iter++;
			}
			writeFile << endl;
		}	
		writeFile.close();
	}
}
