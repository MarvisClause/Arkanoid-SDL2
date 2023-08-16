#pragma once
#include "Framework.h"
#include "SceneObject.h"
#include "BaseObject.h"
#include "SpawnManager.h"
#include "SpriteManager.h"
#include "MapManager.h"
#include "vector2f.h"
#include "GameSettings.h"
#include "Platform.h"
#include "Reticle.h"
#include "Ball.h"
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <algorithm>

class MyFramework : public Framework {

private:
	int window_w;
	int window_h;
	SpriteManager* spriteManager;
	SpawnManager* spawnManager;
	MapManager* mapManager;


public:

	void StartGame();

	void SetGameSettings();

	void SetWindowSize(const int window_w_, const int window_h_);

	void GetScreenSize(int& w, int& h);

	void GetMapSize(int& w, int& h);

	void GetSpriteSize(Sprite* s, int& w, int& h);

	void SetSpritesSize();

	void SetSpiteSize(Sprite* sprite, int w, int h);

	Sprite* LoadSprite(const char* path);

	void DestroySprite(Sprite* s);

	void DrawBackground(Sprite*sprite);

	void DrawMenu();

	void DrawLives();

	void DrawAbilities();

	void DrawScore();

	void DrawSprite(Sprite*sprite, int x, int y);

	void DrawSceneObject(SceneObject* sceneObj);

	virtual void PreInit(int& width, int& height, bool& fullscreen);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

protected:

	virtual const char* GetTitle() override;
};