#include "MyFramework.h"
#include<iostream>
#include<Windows.h>
#include<chrono>

void MyFramework::StartGame()
{

		spawnManager->CreateObj((ObjectType::Platform), spriteManager->getSprite(SpriteTypes::Platform));
		spawnManager->CreateObj((ObjectType::DeathZone), spriteManager->getSprite(SpriteTypes::DeathZone));
		spawnManager->SpawnBlocks();
		spawnManager->CreateObj((ObjectType::Turret), spriteManager->getSprite(SpriteTypes::Turret));
		spawnManager->CreateObj((ObjectType::Reticle), spriteManager->getSprite(SpriteTypes::Reticle));
}

void MyFramework::SetGameSettings()
{

}

void MyFramework::SetWindowSize(const int window_w_, const int window_h_)
{
	window_w = window_w_;
	window_h = window_h_;
}

void MyFramework::GetScreenSize(int& w, int& h)
{
	getScreenSize(w, h);
}

void MyFramework::GetMapSize(int& w, int& h)
{
	GetScreenSize(w, h);
	w = w * GameSettings::GetInstance()->GetMapSize();
}

void MyFramework::GetSpriteSize(Sprite* s, int& w, int& h)
{
	getSpriteSize(s, w, h);
}

void MyFramework::SetSpritesSize()
{
	//I am tired.
	double koef_w = static_cast<double>(window_w) / 1000.;
	double koef_h = static_cast<double>(window_h) / 800.;

	for (auto i : GameSettings::GetInstance()->GetSpriteManager()->getAllSprites())
	{
		int sprite_w, sprite_h;
		getSpriteSize(i, sprite_w, sprite_h);
		setSpriteSize(i, sprite_w*koef_w, sprite_h*koef_h);
	}

	for (auto i : GameSettings::GetInstance()->GetSpriteManager()->getAllScoreSprites())
	{
		int sprite_w, sprite_h;
		getSpriteSize(i, sprite_w, sprite_h);
		setSpriteSize(i, sprite_w * koef_w, sprite_h * koef_h);
	}
}

void MyFramework::SetSpiteSize(Sprite* sprite, int w, int h)
{
	setSpriteSize(sprite, w, h);
}

Sprite* MyFramework::LoadSprite(const char* path)
{
	return createSprite(path);
}

void MyFramework::DestroySprite(Sprite* s)
{
	destroySprite(s);
}


void MyFramework::DrawBackground(Sprite* sprite)
{
	drawSprite(sprite, 0, 0);
}

void MyFramework::DrawMenu()
{
	DrawBackground(spriteManager->getSprite(SpriteTypes::Game_window));
	DrawLives();
	DrawAbilities();
	DrawScore();
}

void MyFramework::DrawLives()
{
	int w, h;
	GetMapSize(w, h);

	int sprite_w, sprite_h;

	spriteManager->getSpriteSize(spriteManager->getSprite(SpriteTypes::Life), sprite_w, sprite_h);
	DrawSprite(spriteManager->getSprite(SpriteTypes::Lives), w+10, sprite_h*0.75);

	for (int i = 0; i < GameSettings::GetInstance()->GetLives(); i++)
	{
		w += sprite_w * 0.25;
		DrawSprite(spriteManager->getSprite(SpriteTypes::Life),w, sprite_h*1.75);
		w += sprite_w / 2;
	}
}

void MyFramework::DrawAbilities()
{
	int map_w, map_h;
	GetMapSize(map_w, map_h);

	int sprite_w, sprite_h;

	spriteManager->getSpriteSize(spriteManager->getSprite(SpriteTypes::Skills), sprite_w, sprite_h);
	
	int w = map_w + 10;
	int h = sprite_h * 3;

	DrawSprite(spriteManager->getSprite(SpriteTypes::Skills), w, h);

	h += sprite_h+5;

	spriteManager->getSpriteSize(spriteManager->getSprite(SpriteTypes::Platform_increase), sprite_w, sprite_h);

	w = w + 0.5 * sprite_w;

	for (auto i : spawnManager->GetPlatformAbilities())
	{
		if (window_w - w> sprite_w)
		{
			DrawSprite(i->GetSprite(), w, h);
		}
		else
		{
			h += sprite_h * 2;
			w = map_w + 0.5 * sprite_w;
			DrawSprite(i->GetSprite(), w, h);
		}	
		w += sprite_w + 10;
	}

	spriteManager->getSpriteSize(spriteManager->getSprite(SpriteTypes::Ball_increase), sprite_w, sprite_h);	
	h += sprite_h;
	w = map_w;

	for (auto i : spawnManager->GetBallAbilities())
	{
		w += sprite_w + 10;

		if (window_w - w > sprite_w)
		{
			DrawSprite(i->GetSprite(), w, h);
		}
		else
		{
			h += sprite_h * 2;
			w = map_w + sprite_w + 10;
			DrawSprite(i->GetSprite(), w, h);
		}
	}
}
void MyFramework::DrawScore()
{
	int map_w, map_h;
	GetMapSize(map_w, map_h);

	int sprite_w, sprite_h;
	spriteManager->getSpriteSize(spriteManager->getSprite(SpriteTypes::Score), sprite_w, sprite_h);

	DrawSprite(spriteManager->getSprite(SpriteTypes::Score), map_w + 10, map_h/2+sprite_h);

	int w, h;
	std::pair<int, int>score;
	score.first = GameSettings::GetInstance()->GetCurrentScore() / 10;
	score.second = GameSettings::GetInstance()->GetCurrentScore() % 10;
	
	spriteManager->getSpriteSize(spriteManager->getScoreSprite(score.first), sprite_w, sprite_h);

	DrawSprite(spriteManager->getScoreSprite(score.first), map_w+sprite_w/2, map_h / 2 + 1.5*sprite_h);
	DrawSprite(spriteManager->getScoreSprite(score.second), map_w + sprite_w*1.5, map_h / 2 + 1.5*sprite_h);
}

void MyFramework::DrawSprite(Sprite*sprite, int x, int y)
{
	drawSprite(sprite, x, y);
}

void MyFramework::DrawSceneObject(SceneObject* sceneObj)
{
	if (sceneObj != nullptr)
	{
		Sprite* sprite = sceneObj->GetSprite();
		vector2f pos = sceneObj->GetPosition();
		int sprite_h = sceneObj->GetSpriteHeight();
		int sprite_w = sceneObj->GetSpriteWidth();

		Platform* platform = GameSettings::GetInstance()->GetSpawnManager()->platform;

		if (sprite != nullptr)
		{
			drawSprite(sprite, pos.x - sprite_w / 2, pos.y - sprite_h / 2);
		}
	}
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	
	width = window_w;
	height = window_h;
	fullscreen = false;

	spriteManager = new SpriteManager(this);
	GameSettings::GetInstance()->SetSpriteManager(spriteManager);

	spawnManager = new SpawnManager(this);
	GameSettings::GetInstance()->SetSpawnManager(spawnManager);

	mapManager = new MapManager(this);
	GameSettings::GetInstance()->SetMapManager(mapManager);

	GameSettings::GetInstance()->SetFramework(this);
}

bool MyFramework::Init()
{
	srand(time(NULL));

	if (!spriteManager->LoadSprites())
	{
		return false;
	}
	SetSpritesSize();

	StartGame();

	showCursor(false);

	return true;
}

void MyFramework::Close()
{
	spriteManager->DestroySprites();
	GameSettings::GetInstance()->GetSpawnManager()->DestroyAllObjects();
}

bool MyFramework::Tick()
{
	srand(time(NULL));
	
	if (GameSettings::GetInstance()->isGameOver.first)
	{
		if (GameSettings::GetInstance()->isGameOver.second)
		{
			DrawBackground(spriteManager->
				getSprite(SpriteTypes::Win_screen));
		}
		else 
		{
			DrawBackground(spriteManager->
				getSprite(SpriteTypes::Lose_screen));
		}
		auto start = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = start - GameSettings::GetInstance()->screenTime;
		if (elapsed_seconds.count() > GameSettings::GetInstance()->GetEndGameScreenTimer())
		{
			GameSettings::GetInstance()->RestartGame();
		}
		return false;
	}

	DrawMenu();

	std::vector<SceneObject*> sceneObjects = spawnManager->GetSceneObjects();

	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i]->move();

		for (size_t j = 0; j < sceneObjects.size(); j++)
		{
			sceneObjects[i]->updateCollision(sceneObjects[j]);
		}

		DrawSceneObject(sceneObjects[i]);
	}

	GameSettings::GetInstance()->GameLoseCheck();

	spawnManager->FinishDeleting();

	spawnManager->SetBlockCollisionFalse();

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	spawnManager->reticle->SetPosition(x,y);
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (button == FRMouseButton::LEFT && !isReleased)
	{
		spawnManager->CreateObj((ObjectType::Ball), spriteManager->getSprite(SpriteTypes::Ball));
		spawnManager->DestroyObject(spawnManager->reticle);
	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	spawnManager->platform->processKeyPressed(k);
}

void MyFramework::onKeyReleased(FRKey k)
{
	spawnManager->platform->processKeyReleased(k);
}

const char* MyFramework::GetTitle()
{
	return "Arkanoid";
}



