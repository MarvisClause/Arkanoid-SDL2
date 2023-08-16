#include"GameSettings.h"
#include"SpriteManager.h"
#include"SpawnManager.h"
#include<Windows.h>

GameSettings* GameSettings::settings = nullptr;

SpriteManager* GameSettings::GetSpriteManager()
{
	return spriteManager;
}

SpawnManager* GameSettings::GetSpawnManager()
{
	return spawnManager;
}

MapManager* GameSettings::GetMapManager()
{
	return mapManager;
}

MyFramework* GameSettings::GetFramework()
{
	return framework;
}

void GameSettings::SetSpriteManager(SpriteManager* mgr)
{
	spriteManager = mgr;
}

void GameSettings::SetSpawnManager(SpawnManager* mgr)
{
	spawnManager = mgr;
}

void GameSettings::SetMapManager(MapManager* mgr)
{
	mapManager = mgr;
}

void GameSettings::SetFramework(MyFramework* framework_)
{
	framework = framework_;
}

void GameSettings::GetWindowSize(int& w, int& h)
{
	getScreenSize(w, h);
}

void GameSettings::GetMapSize(int& w, int& h)
{
	int window_w, window_h;
	GetWindowSize(window_w, window_h);
	w = window_w * MAP_SIZE; 
	h = window_h;
} 
//We should have gone to the fireman.

void GameSettings::GameLoseCheck()
{
	if (Lives == 0)
	{
		isGameOver = { true,false };
		screenTime = std::chrono::system_clock::now();
	}
}

void GameSettings::GameWinCheck()
{
	if (spawnManager->GetBlocksAmount() == 0)
	{
		isGameOver = { true,true };
		screenTime = std::chrono::system_clock::now();
	}
}

void GameSettings::RestartGame()
{
	isGameOver = { false,false };
	GetSpawnManager()->DestroyAllObjects();
	Lives = 3;
	CURRENT_SCORE = 0;
	framework->SetSpiteSize(spriteManager->getSprite(SpriteTypes::Platform), START_PLATFORM_SIZE.first, START_PLATFORM_SIZE.second);
	framework->SetSpiteSize(spriteManager->getSprite(SpriteTypes::Ball), START_BALL_SIZE.first, START_BALL_SIZE.second);
	mapManager->SetMap();
	framework->StartGame();
}

GameSettings* GameSettings::GetInstance()
{
	if (settings == nullptr)
	{
		settings = new GameSettings();
	}
	return settings;
}

int GameSettings::GetBallSpeed()
{
	return BALL_SPEED;
}

int GameSettings::GetPlatformSpeed()
{
	return PLATFORM_SPEED;
}

int GameSettings::GetPlatformAboveWindow()
{
	return PLATFORM_ABOVE_WINDOW;
}

int GameSettings::GetMaxBlocks()
{
	return MAX_BLOCKS;
}

int GameSettings::GetThresholdRadius()
{
	return THRESHOLD_RADIUS;
}

float GameSettings::GetMapSize()
{
	return MAP_SIZE;
}

int GameSettings::GetLives()
{
	return Lives;
}

float GameSettings::GetAbilityProbability()
{
	return ABILITY_PROB;
}

std::pair<int, int> GameSettings::GetStartPlatformSize()
{
	return START_PLATFORM_SIZE;
}

std::pair<int, int> GameSettings::GetStartBallSize()
{
	return START_BALL_SIZE;
}

int GameSettings::GetTurretSpeed()
{
	return TURRET_SPEED;
}

int GameSettings::GetEndGameScreenTimer()
{
	return ENDGAME_SCREEN_TIMER;
}

int GameSettings::GetCurrentScore()
{
	return CURRENT_SCORE;
}

void GameSettings::SetBallSpeed(int ballSpeed)
{
	BALL_SPEED = ballSpeed;
}

void GameSettings::SetPlatformSpeed(int platformSpeed)
{
	PLATFORM_SPEED = platformSpeed;
}

void GameSettings::SetPlatformAboveWindow(int aboveWindow)
{
	PLATFORM_ABOVE_WINDOW = aboveWindow;
}

void GameSettings::SetMaxBlocks(int maxBlocks)
{
	MAX_BLOCKS = maxBlocks;
}

void GameSettings::SetThresholdRadius(int thresholdRadius)
{
	THRESHOLD_RADIUS = thresholdRadius;
}

void GameSettings::SetMapSize(float mapSize)
{
	MAP_SIZE = mapSize;
}

void GameSettings::SetLives(int Lives_)
{
	Lives = Lives_;
}

void GameSettings::SetAbilityProbability(float ability_prob)
{
	ABILITY_PROB = ability_prob;
}

void GameSettings::SetStartPlatformSize(int w, int h)
{
	START_PLATFORM_SIZE.first = w;
	START_PLATFORM_SIZE.second = h;
}

void GameSettings::SetStartBallSize(int w, int h)
{
	START_BALL_SIZE.first = w;
	START_BALL_SIZE.second = h;
}

void GameSettings::SetTurretSpeed(int speed)
{
	TURRET_SPEED = speed;
}

void GameSettings::SetEndGameScreenTimer(int time)
{
	ENDGAME_SCREEN_TIMER = time;
}

void GameSettings::IncrementCurrentScore()
{
	CURRENT_SCORE++;
}


