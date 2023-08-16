#include "Turret.h"
#include"GameSettings.h"

Turret::Turret(Sprite* sprite):SceneObject(sprite)
{
	int w, h;
	GameSettings::GetInstance()->GetMapSize(w, h);

	int sprite_w, sprite_h;

	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, sprite_w, sprite_h);

	position.x = w / 2;
	position.y = sprite_h;
}

void Turret::processCollision(SceneObject* sceneObj)
{

}

void Turret::move()
{
	change_dir_time -= 0.002;
	shoot_time -= 0.002;

	if (shoot_time <= 0)
	{
		Shoot();
		shoot_time = 10;
	}

	if (change_dir_time <= 0)
	{
		RandDirection();
		change_dir_time = 3;
	}

	isWall();
	position = position + direction * GameSettings::GetInstance()->GetTurretSpeed();
}

ObjectType Turret::GetObjectType()
{
	return ObjectType::Turret;
}

void Turret::Shoot()
{
	GameSettings::GetInstance()->GetSpawnManager()->CreateObj(
		ObjectType::TurretBullet, GameSettings::GetInstance()->GetSpriteManager()->getSprite(SpriteTypes::TurretBullet));
}

void Turret::isWall()
{
	int w, h;
	GameSettings::GetInstance()->GetMapSize(w, h);
	int sprite_w, sprite_h;
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(sprite, sprite_w, sprite_h);

	if (position.x <= sprite_w / 2 || position.x >= w - sprite_w / 2) direction.x *= -1;
	if (position.y <= sprite_h / 2 || position.y >=140 - sprite_h/2) direction.y *= -1;
}

void Turret::RandDirection()
{
	srand(time(NULL));
	int value = rand() % 3;

	if (value == 2) value = -1;
	direction.x = static_cast<double>(value)/10.;

	value = rand() % 3;
	if (value == 2) value = -1;
	direction.y = static_cast<double>(value)/10.;
}
