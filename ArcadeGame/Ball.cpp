#include "Ball.h"
#include "GameSettings.h"

#include<cmath>

Ball::Ball(Sprite* sprite, vector2f platform_pos, vector2f direction_): SceneObject(sprite)
{
	position = platform_pos;
	direction_ = direction_ - position;

	float len = sqrt(direction_.x * direction_.x + direction_.y * direction_.y);
	direction_ = direction_ / len;

	direction = direction_;
}

void Ball::processCollision(SceneObject* sceneObj)
{
	if (sceneObj->GetObjectType() == ObjectType::Platform)
	{
		GameSettings::GetInstance()->GameWinCheck();
		changeBallDirection(sceneObj);
	}
	else if (sceneObj->GetObjectType()==ObjectType::DeathZone)
	{
		GameSettings::GetInstance()->SetLives(GameSettings::GetInstance()->GetLives() - 1);
		GameSettings::GetInstance()->GetSpawnManager()->CreateObj(ObjectType::Reticle,
			GameSettings::GetInstance()->GetSpriteManager()->getSprite(SpriteTypes::Reticle));
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	}
	else if (sceneObj->GetObjectType() == ObjectType::Solid_block && !collisionBlock)
	{
		GameSettings::GetInstance()->IncrementCurrentScore();

		GameSettings::GetInstance()->GetSpawnManager()->GenerateAbility(sceneObj->GetPosition());
		
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(sceneObj);

		changeBallDirection(sceneObj);
		collisionBlock = true;
	}
}

void Ball::move()
{
	isWall();
	position = position + direction * GameSettings::GetInstance()->GetBallSpeed();
}

ObjectType Ball::GetObjectType()
{
	return ObjectType::Ball;
}

void Ball::SetCollisionBlock()
{
	collisionBlock = false;
}

void Ball::isWall()
{
	int w,h;
	GameSettings::GetInstance()->GetMapSize(w, h);
	int sprite_w, sprite_h;
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, sprite_w, sprite_h);
	
	int platform_above_window = GameSettings::GetInstance()->GetPlatformAboveWindow();
	
	if (position.x <= sprite_w / 2 || position.x >= w - sprite_w/2) direction.x *= -1;
	if (position.y <= sprite_h / 2) direction.y *= -1;
}

void Ball::changeBallDirection(SceneObject* sceneObj)
{
	vector2f platform_pos = sceneObj->GetPosition();

	vector2f direction_ = position - platform_pos;

	float len = sqrt(direction_.x * direction_.x + direction_.y * direction_.y);

	direction = direction_ / len;
}

