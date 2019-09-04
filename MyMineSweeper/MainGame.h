#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
using namespace std;

enum GAME_STATE
{
	GAME_STATE_PLAY,
	GAME_STATE_LOSE,
	GAME_STATE_WIN,
	GAME_STATE_WAIT
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
	Block*			m_pSelect;
	int				m_iVecHeight;
	int				m_iVecWidth;
	int				m_iMineNum;
	int				m_iFlagNum;
	int				m_iTime;
	HWND			m_hWnd;
	GAME_STATE		m_eState;
	int				m_iTimeCount = 10;


public:
	static MainGame* GetInstance();
	void SetVecHeightAndWidth(int height, int width);
	void SetVecBlock();
	void DeleteVecBlock();
	void SetMineNum(int num);
	void ShuffleMine();
	void SetBlockNumber();
	void ClickBlockEmpty(int i, int j);
	void DrawMineNum(HDC hdc);
	void SetTime();
	inline void SetGameStatePlay()
	{
		m_eState = GAME_STATE_PLAY;
	}
	bool IsWin();
	void AllOpen();
	void DrawTime(HDC hdc);
public:
	void Init(HWND hWnd, HDC hdc);
	void Draw(HDC hdc);
	void Update();
	void LBInput(POINT pt);
	void RbInput(POINT pt);
	void Release();
private:
	MainGame();
public:
	~MainGame();
};

