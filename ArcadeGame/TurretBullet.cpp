#include "TurretBullet.h"
#include "GameSettings.h"
#include"Turret.h"

#include<cmath>

TurretBullet::TurretBullet(Sprite* sprite):SceneObject(sprite)
{
	position = GameSettings::GetInstance()->GetSpawnManager()->turret->GetPosition();
	vector2f platform_pos = GameSettings::GetInstance()->GetSpawnManager()->platform->GetPosition();
	vector2f coords = platform_pos - position;
	float len = sqrt(coords.x*coords.x + coords.y*coords.y);
	direction = coords/ len;
}

void TurretBullet::processCollision(SceneObject* sceneObj)
{
	if (sceneObj->GetObjectType() == ObjectType::DeathZone)
	{
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	}
	else if (sceneObj->GetObjectType() == ObjectType::Platform)
	{
		GameSettings::GetInstance()->SetLives(GameSettings::GetInstance()->GetLives() - 1);
		GameSettings::GetInstance()->GameLoseCheck();
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	}
}

void TurretBullet::move()
{
	position= position + direction;
}

ObjectType TurretBullet::GetObjectType()
{
	return ObjectType::TurretBullet;
}
