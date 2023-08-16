#include"SpriteManager.h"
#include"MyFramework.h"

SpriteManager::SpriteManager(MyFramework* framework)
{
	this->framework = framework;
}

bool SpriteManager::LoadSprites()
{
	for (int i = 0; i < static_cast<unsigned int>(SpriteTypes::Max); i++)
	{
		Sprite* temp = framework->LoadSprite(spritePath[i]);
		if (temp)
		{
			Sprites.push_back(temp);
		}
		else
		{
			return false;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Sprite* temp = framework->LoadSprite(scoreSpritePath[i]);
		if (temp)
		{
			ScoreSprites.push_back(temp);
		}
		else
		{
			return false;
		}
	}

	return true;
}

Sprite* SpriteManager::getSprite(SpriteTypes sprite)
{
	return Sprites[static_cast<unsigned int>(sprite)];
}

Sprite* SpriteManager::getScoreSprite(const int num)
{
	return ScoreSprites[num];
}

void SpriteManager::getSpriteSize(Sprite* sprite, int& w, int& h)
{
	framework->GetSpriteSize(sprite, w, h);
}

void SpriteManager::DestroySprites()
{
	for (int i = 0; i < static_cast<unsigned int>(SpriteTypes::Max);i++)
	{
		framework->DestroySprite(Sprites[static_cast<unsigned int> (i)]);
	}
}

std::vector<Sprite*> SpriteManager::getAllSprites()
{
	return Sprites;
}

std::vector<Sprite*> SpriteManager::getAllScoreSprites()
{
	return ScoreSprites;
}
