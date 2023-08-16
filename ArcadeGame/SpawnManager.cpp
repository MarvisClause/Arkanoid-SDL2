#include "SpawnManager.h"
#include "GameSettings.h"
#include "SpriteManager.h"
//-------------------------//
#include "Platform.h"
#include"Ball.h"
#include"Reticle.h"
#include"SolidBlock.h"
#include"DeathZone.h"
#include "Ability.h"
#include "Turret.h"
#include"TurretBullet.h"
#include<Windows.h>
#include<vector>

SpawnManager::SpawnManager(MyFramework* framework)
{
	this->framework = framework;
}

std::vector<SceneObject*> SpawnManager::GetSceneObjects()
{
	return sceneObjects;
}

std::vector<SceneObject*> SpawnManager::GetPlatformAbilities()
{
	return platform_abilities;
}

std::vector<SceneObject*> SpawnManager::GetBallAbilities()
{
	return ball_abilities;
}

void SpawnManager::CreateObj(ObjectType sprType_, Sprite* sprite)
{
	switch (sprType_)
	{
	case ObjectType::Platform:
		platform = new Platform(sprite);
		sceneObjects.push_back(platform);
		break;
	case ObjectType::Reticle:
		CreateReticle(sprite);
		break;
	case ObjectType::Solid_block:
		for(int i=0; i< GameSettings::GetInstance()->GetMapManager()->GetBlocks().size();i++)
		{
			CreateSolidBlock(sprite, GameSettings::GetInstance()->GetMapManager()->GetBlocks()[i]);
		}
		break;
	case ObjectType::TurretBullet:
		turret_bullet = new TurretBullet(sprite);
		sceneObjects.push_back(turret_bullet);
		break;
	case ObjectType::Ball:
		CreateBall(sprite);
		break;
	case ObjectType::DeathZone :
		deathZone = new DeathZone(sprite);
		sceneObjects.push_back(deathZone);
		break;
	case ObjectType::Turret :
		turret = new Turret(sprite);
		sceneObjects.push_back(turret);
		break;
	case ObjectType::Max:
		break;
	default:
		break;
	}
}
//How many sleepless nights have i had?
void SpawnManager::DestroyObject(SceneObject* sceneObj)
{
	objectsToDelete.push_back(sceneObj);
}

void SpawnManager::SpawnBlocks()
{
	if (blocks.empty())
	{
		CreateObj(ObjectType::Solid_block, GameSettings::GetInstance()->
			GetSpriteManager()->getSprite(SpriteTypes::Solid_block));
	}
}

void SpawnManager::FinishDeleting()
{
	for (int i = 0; i < objectsToDelete.size(); i++)
	{
		SceneObject* del = objectsToDelete[i];

		if (!del)
		{
			continue;
		}

		auto it = find(sceneObjects.begin(), sceneObjects.end(), del);
		if (it != sceneObjects.end())
		{
			sceneObjects.erase(it);
		}
		if ((find(balls.begin(), balls.end(), del)) != balls.end())
		{
			balls.erase(find(balls.begin(), balls.end(), del));
		}
		if ((find(blocks.begin(), blocks.end(), del)) != blocks.end())
		{
			blocks.erase(find(blocks.begin(), blocks.end(), del));
		}
		if ((find(ball_abilities.begin(), ball_abilities.end(), del)) != ball_abilities.end())
		{
			ball_abilities.erase(find(ball_abilities.begin(), ball_abilities.end(), del));
		}
		if ((find(platform_abilities.begin(), platform_abilities.end(), del)) != platform_abilities.end())
		{
			platform_abilities.erase(find(platform_abilities.begin(), platform_abilities.end(), del));
		}
	}
	objectsToDelete.clear();
}

void SpawnManager::DestroyAllObjects()
{
	balls.clear();
	sceneObjects.clear();
	objectsToDelete.clear();
	blocks.clear();
	ball_abilities.clear();
	platform_abilities.clear();
}


void SpawnManager::GenerateAbility(vector2f position)
{
	if (CheckAbilitySpawn())
	{
		int num = rand() % 4;
		Sprite* ability_sprite;
		ObjectType affected_object;
		switch (num)
		{
		case 0:	
			CreateAbility(SpriteTypes::Platform_increase, position, 1.4, ObjectType::Platform);
			break;
		case 1:
			CreateAbility(SpriteTypes::Platform_decrease, position, 0.714, ObjectType::Platform);
			break;
		case 2:
			CreateAbility(SpriteTypes::Ball_increase, position, 1.4, ObjectType::Ball);
			break;
		case 3:
			CreateAbility(SpriteTypes::Ball_decrease, position, 0.714, ObjectType::Ball);
			break;
		default:
			break;
		}
		
	}
}

int SpawnManager::GetBallsAmount()
{
	return balls.size();
}

int SpawnManager::GetBlocksAmount()
{
	return blocks.size();
}

SceneObject* SpawnManager::CreateAbility(SpriteTypes type, vector2f pos, float koef, ObjectType affected_object)
{
	Sprite* ability_sprite = GameSettings::GetInstance()->GetSpriteManager()->getSprite(type);
	ability = new Ability(ability_sprite, pos, koef, affected_object);
	
	sceneObjects.push_back(ability);
	return ability;
}

void SpawnManager::PushBackPlatformAbility(SceneObject* ability)
{
	platform_abilities.push_back(ability);
}

void SpawnManager::PushBackBallAbility(SceneObject* ability)
{
	ball_abilities.push_back(ability);
}

std::vector<SceneObject*> SpawnManager::GetBlocks()
{
	return blocks;
}

void SpawnManager::SetBlockCollisionFalse()
{
	for (auto i : balls)
	{
		i->SetCollisionBlock();
	}
}

bool SpawnManager::CheckAbilitySpawn()
{
	if (rand() % 10 < GameSettings::GetInstance()->GetAbilityProbability() * 10)
	{
		return true;
	}
	return false;
}


void SpawnManager::CreateReticle(Sprite* sprite)
{
	int w, h;
	GameSettings::GetInstance()->GetWindowSize(w, h);
	vector2f temp = { w, h };
	reticle = new Reticle(sprite, temp);
	sceneObjects.push_back(reticle);
}

void SpawnManager::CreateBall(Sprite* sprite)
{
	if (balls.empty())
	{
		int ball_w, ball_h;
		int platform_w, platform_h;
		GameSettings::GetInstance()->GetSpriteManager()->
			getSpriteSize(GameSettings::GetInstance()->GetSpriteManager()->
				getSprite(SpriteTypes::Platform), platform_w, platform_h);

		GameSettings::GetInstance()->GetSpriteManager()->
			getSpriteSize(sprite, ball_w, ball_h);
		vector2f dir = reticle->GetPosition();
		vector2f pos = platform->GetPosition();
		pos.y -= ball_h / 2 + platform_h / 2;

		Ball* ball = new Ball(sprite, pos, dir);
		balls.push_back(ball);
		sceneObjects.push_back(ball);
	}

}

SceneObject* SpawnManager::CreatePlatform(Sprite* sprite, vector2f position_)
{
	platform = new Platform(sprite,position_);
	sceneObjects.push_back(platform);
	return platform;
}

void SpawnManager::CreateSolidBlock(Sprite* sprite, vector2f position)
{
	solidBlock = new SolidBlock(sprite, position);
	blocks.push_back(solidBlock);
	sceneObjects.push_back(solidBlock);
}

bool SpawnManager::isBlocked(vector2f position, int sprite_w, int sprite_h)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		if ((abs(blocks[i]->GetPosition().x - position.x) < sprite_w) && (abs(blocks[i]->GetPosition().y - position.y) < sprite_h))
		{
			return true;
		}
	}
	return false;
}

