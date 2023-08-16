#pragma once
#include"BaseObject.h"
#include<vector>

class MyFramework;
class Sprite;

enum class SpriteTypes
{
	Platform,
	Reticle,
	Solid_block,
	Ball,
	DeathZone,
	Turret,
	TurretBullet,
	Platform_increase,
	Platform_decrease,
	Ball_increase,
	Ball_decrease,
	Game_window,
	Lose_screen,
	Win_screen,
	Life,
	Lives,
	Skills,
	Score,
	Max
};

class SpriteManager : public BaseObject
{
public:
	SpriteManager(MyFramework* framework);

	bool LoadSprites();

	Sprite* getSprite(SpriteTypes sprite);
	Sprite* getScoreSprite(const int num);

	void getSpriteSize(Sprite* sprite, int& w, int& h);

	void DestroySprites();

	std::vector<Sprite*>getAllSprites();
	std::vector<Sprite*>getAllScoreSprites();

private:
	MyFramework* framework;

	std::vector<Sprite*> ScoreSprites;
	std::vector<Sprite*> Sprites;

	const char* spritePath[static_cast<unsigned int> (SpriteTypes::Max)] = {
	"data/Platform.png",
	"data/Reticle.png",
	"data/SolidBlock1.png",
	"data/Ball1.png",
	"data/DeathZone.jpg",
	"data/Turret.png",
	"data/TurretBullet.png",
	"data/Platform_increase.png",
	"data/Platform_decrease.png",
	"data/Ball_increase.png",
	"data/Ball_decrease.png",
	"data/Background.png",
	"data/LoseScreen.png",
	"data/WinScreen.png",
	"data/Life.png",
	"data/Lives.png",
	"data/Skills.png",
	"data/Score.png"
	};

	const char* scoreSpritePath[10] = {
		"data/Score/score0.png",
		"data/Score/score1.png",
		"data/Score/score2.png",
		"data/Score/score3.png",
		"data/Score/score4.png",
		"data/Score/score5.png",
		"data/Score/score6.png",
		"data/Score/score7.png",
		"data/Score/score8.png",
		"data/Score/score9.png"
	};
};