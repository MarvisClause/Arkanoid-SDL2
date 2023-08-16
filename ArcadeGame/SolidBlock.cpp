#include "SolidBlock.h"
#include "GameSettings.h"

SolidBlock::SolidBlock(Sprite* sprite, vector2f pos):SceneObject(sprite)
{
	position = pos;
}

void SolidBlock::processCollision(SceneObject* sceneObj)
{
	if (sceneObj->GetObjectType() == ObjectType::DeathZone)
	{
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	}
	if (sceneObj->GetObjectType() == ObjectType::Platform)
	{
		GameSettings::GetInstance()->SetLives(GameSettings::GetInstance()->GetLives() - 1);
		GameSettings::GetInstance()->GameLoseCheck();
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	}
}

void SolidBlock::move()
{
	if (isBottomLine() && !isBlockOnTop())
	{
		position.y += 1;
	}
}

ObjectType SolidBlock::GetObjectType()
{
	return ObjectType::Solid_block;
}

bool SolidBlock::isBottomLine()
{
	for (auto i : GameSettings::GetInstance()->GetSpawnManager()->GetBlocks())
	{
		if (i->GetPosition().y > position.y)
		{
			return false;
		}
	}
	return true;
}

bool SolidBlock::isBlockOnTop()
{
	int sprite_w, sprite_h;
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(
		GameSettings::GetInstance()->GetSpriteManager()->getSprite(SpriteTypes::Solid_block), sprite_w, sprite_h);
	for (auto i : GameSettings::GetInstance()->GetSpawnManager()->GetBlocks())
	{
		if (abs(i->GetPosition().x - position.x) < sprite_w && position.y - i->GetPosition().y == sprite_h)
		{
			return true;
		}
	}
	return false;
}

