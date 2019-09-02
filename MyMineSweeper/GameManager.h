#pragma once

enum GAME_MODE
{
	GAME_MODE_EASY,
	GAME_MODE_NOMAL,
	GAME_MODE_HARD
};

class GameManager
{
private:
	static GameManager* m_sThis;
	//GAME_MODE m_eMode;
public:
	static GameManager* GetInstance();
	void SetGameMode(GAME_MODE eMode);
private:
	GameManager();
public:
	~GameManager();
};

