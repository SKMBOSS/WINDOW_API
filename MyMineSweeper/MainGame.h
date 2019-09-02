#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
using namespace std;

enum GAME_STATE
{
	GAME_STATE_WAIT,
	GAME_STATE_ONE,
	GAME_STATE_SHOW
};

class ResManager;
class Block;
class BitMap;
class MainGame
{
private:
	static MainGame* m_sThis;
	ResManager*		m_pResManager;
	BitMap*			m_pBackGround;
	vector<Block*>	m_vecBlock;
	int				m_iVecHeight;
	int				m_iVecWidth;
	HWND			m_hWnd;
	//GAME_STATE		m_eState;
	Block*			m_pSelect;

public:
	static MainGame* GetInstance();
	void SetVecHeightAndWidth(int height, int width);
	void SetVecBlock();
	void DeleteVecBlock();
public:
	void Init(HWND hWnd, HDC hdc);
	void Draw(HDC hdc);
	void Update();
	void Input(POINT pt);
	void Release();
private:
	MainGame();
public:
	~MainGame();
};

