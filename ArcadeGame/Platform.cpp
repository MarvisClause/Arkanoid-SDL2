#include "Platform.h"
#include "GameSettings.h"
#include "MyFramework.h"

#include <iostream>

Platform::Platform(Sprite* sprite) : SceneObject(sprite)
{
	int w, h;
	GameSettings::GetInstance()->GetMapSize(w, h);

	int sprite_w, sprite_h;

	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, sprite_w, sprite_h);
	
	position.x = w / 2;
	position.y = h - sprite_h/2 - GameSettings::GetInstance()->GetPlatformAboveWindow();
}

Platform::Platform(Sprite* sprite, vector2f pos) : SceneObject(sprite)
{
	position = pos;
}

SceneObject* Platform::PlatfromAbilityUpdate()
{
	SceneObject* temp = GameSettings::GetInstance()->GetSpawnManager()->CreatePlatform(GameSettings::GetInstance()->
		GetSpriteManager()->getSprite(SpriteTypes::Platform), position);
	GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	return temp;
}

void Platform::processKeyPressed(FRKey k)
{
	int platform_speed = GameSettings::GetInstance()->GetPlatformSpeed();
	
	switch (k)
	{
	case FRKey::RIGHT:
			movement = platform_speed;
		break;

	case FRKey::LEFT:
			movement = - platform_speed;
		break;
	}


}

void Platform::processKeyReleased(FRKey k)
{
	movement = 0;
}

void Platform::processCollision(SceneObject*)
{
	return;
}

void Platform::move()
{
	if (isLeftWall() && movement < 0) return;
	if (isRightWall() && movement > 0) return;
	position.x += movement;
}


ObjectType Platform::GetObjectType()
{
	return ObjectType::Platform;
}

bool Platform::isRightWall()
{
	int window_w, window_h;
	GameSettings::GetInstance()->GetMapSize(window_w,window_h);
	
	int platform_w, platform_h;
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, platform_w, platform_h);

	if (position.x + platform_w/2 >= window_w)
	{
		return true;
	}
	return false;
}

bool Platform::isLeftWall()
{
	int platform_w, platform_h;
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, platform_w, platform_h);

	if (position.x <= platform_w/2)
	{
		return true;
	}
	return false;
}
