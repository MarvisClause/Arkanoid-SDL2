#include"DeathZone.h"
#include "GameSettings.h"
#include "MyFramework.h"

DeathZone::DeathZone(Sprite* sprite) :SceneObject(sprite)
{

	
	int map_w, map_h;

	GameSettings::GetInstance()->GetFramework()->GetMapSize(map_w, map_h);

	int sprite_w, sprite_h;
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, sprite_w, sprite_h);

	position.x = map_w/2;
	position.y = map_h - sprite_h/2;
}

void DeathZone::processCollision(SceneObject*)
{

}

void DeathZone::move()
{
}

ObjectType DeathZone::GetObjectType()
{
	return ObjectType::DeathZone;
}
