#pragma once
#include"MyFramework.h"
#include<chrono>

class SpawnManager;
class SpriteManager;
class MapManager;

class GameSettings
{
public:

	std::chrono::system_clock::time_point screenTime;
	std::pair<bool, bool> isGameOver = { false,false };

	SpriteManager* GetSpriteManager();
	SpawnManager* GetSpawnManager();
	MapManager* GetMapManager();
	MyFramework* GetFramework();

	void SetSpriteManager(SpriteManager* mgr);
	void SetSpawnManager(SpawnManager* mgr);
	void SetMapManager(MapManager* mgr);
	void SetFramework(MyFramework* framework_);

	void GetWindowSize(int& w, int& h);
	void GetMapSize(int& w, int& h);
	void GameLoseCheck();
	void GameWinCheck();
	void RestartGame();

	static GameSettings* GetInstance();

	int GetBallSpeed();
	int GetPlatformSpeed();
	int GetPlatformAboveWindow();
	int GetMaxBlocks();
	int GetThresholdRadius();
	float GetMapSize();
	int GetLives();
	float GetAbilityProbability();
	std::pair<int, int>GetStartPlatformSize();
	std::pair<int, int>GetStartBallSize();
	int GetTurretSpeed();
	int GetEndGameScreenTimer();
	int GetCurrentScore();

	void SetBallSpeed(int ballSpeed);
	void SetPlatformSpeed(int platformSpeed);
	void SetPlatformAboveWindow(int aboveWindow);
	void SetMaxBlocks(int maxBlocks);
	void SetThresholdRadius(int thresholdRadius);
	void SetMapSize(float mapSize);
	void SetLives(int Lives_);
	void SetAbilityProbability(float ability_prob);
	void SetStartPlatformSize(int w, int h);
	void SetStartBallSize(int w, int h);
	void SetTurretSpeed(int speed);
	void SetEndGameScreenTimer(int time);
	void IncrementCurrentScore();

protected:
	GameSettings() {};

	static GameSettings* settings;

	SpriteManager* spriteManager;
	SpawnManager* spawnManager;
	MapManager* mapManager;
	MyFramework* framework;

	int CURRENT_SCORE = 0;
	int ENDGAME_SCREEN_TIMER = 3;
	int Lives = 3;
	float MAP_SIZE = 0.7;
	int THRESHOLD_RADIUS = 200;
	int MAX_BLOCKS = 5;
	int BALL_SPEED = 2;
	int PLATFORM_SPEED = 2;
	int PLATFORM_ABOVE_WINDOW = 70;
	float ABILITY_PROB = 0.2;
	int TURRET_SPEED = 1;
	std::pair<int, int>START_BALL_SIZE ={24,24};
	std::pair<int, int>START_PLATFORM_SIZE = {120,32};
};