#include "Ability.h"
#include "GameSettings.h"


Ability::Ability(Sprite* sprite, vector2f pos, float koef_, ObjectType affected_object_) : SceneObject(sprite)
{
	affected_object = affected_object_;
	position = pos;
	koef = koef_;
}

void Ability::processCollision(SceneObject* sceneObj)
{
	if (sceneObj->GetObjectType() == ObjectType::Solid_block)
	{
		if (sceneObj->GetPosition().y > position.y)
		{
			position.y -= fall_speed;
		}		
	}
	else if (sceneObj->GetObjectType() == ObjectType::DeathZone)
	{
		//GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
	}
	else if (sceneObj->GetObjectType() == ObjectType::Platform && !activated)
	{
		if (affected_object == ObjectType::Platform)
		{
			if (ChangePlatformSize(sceneObj))
			{
				activated = true;
				GameSettings::GetInstance()->GetSpawnManager()->PushBackPlatformAbility(this);
			}
				
			else
				GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
		}
		else
		{
			if (ChangeBallSize(sceneObj))
			{
				activated = true;
				GameSettings::GetInstance()->GetSpawnManager()->PushBackBallAbility(this);
			}	
			else
				GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
		}
	}
}

void Ability::move()
{
	position.y += fall_speed;
	time -= 0.002; 
	if (time <= 0)
	{
		AbilityEnd();
	}
}

ObjectType Ability::GetObjectType()
{
	return ObjectType::Ability;
}

bool Ability::ChangeBallSize(SceneObject* sceneObj)
{
	int sprite_w, sprite_h;
	std::pair<int, int>start_size;
	
	affected_sprite = GameSettings::GetInstance()->GetSpriteManager()->getSprite(SpriteTypes::Ball);
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(affected_sprite, sprite_w, sprite_h);
	start_size = GameSettings::GetInstance()->GetStartBallSize();

	double mult_koef = static_cast<double>(sprite_w * sprite_h) / static_cast<double>(start_size.first * start_size.second);

	if ((mult_koef > 0.5 || koef > 1) && (mult_koef < 1.9 || koef < 1))
	{
		sprite_w = static_cast<float>(sprite_w) * koef;
		sprite_h = static_cast<float>(sprite_h) * koef;
		GameSettings::GetInstance()->GetFramework()->SetSpiteSize(affected_sprite, sprite_w, sprite_h);

		return true;
	}
	return false;
}

bool Ability::ChangePlatformSize(SceneObject * sceneObj)
{
	int sprite_w, sprite_h;
	std::pair<int, int>start_size;

	affected_sprite = GameSettings::GetInstance()->GetSpriteManager()->getSprite(SpriteTypes::Platform);
	GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(affected_sprite, sprite_w, sprite_h);
	start_size = GameSettings::GetInstance()->GetStartPlatformSize();

	double mult_koef = static_cast<double>(sprite_w * sprite_h) / static_cast<double>(start_size.first * start_size.second);

	if ((mult_koef > 0.5 || koef > 1) && (mult_koef < 1.9 || koef < 1))
	{
		sprite_w = static_cast<float>(sprite_w) * koef;
		GameSettings::GetInstance()->GetFramework()->SetSpiteSize(affected_sprite, sprite_w, sprite_h);
		activated = true;

		GameSettings::GetInstance()->GetSpawnManager()->platform->PlatfromAbilityUpdate();

		return true;
	}

	return false;
}

void Ability::AbilityEnd()
{
		if (affected_sprite)
		{
			GameSettings::GetInstance()->GetSpriteManager()->getSpriteSize(affected_sprite, sprite_w, sprite_h);
			sprite_w = static_cast<float>(sprite_w) / koef;
			
			if (affected_object == ObjectType::Ball)
			{
				sprite_h = static_cast<float>(sprite_h) / koef;
			}

			GameSettings::GetInstance()->GetFramework()->SetSpiteSize(affected_sprite, sprite_w, sprite_h);
		    
			if (affected_object == ObjectType::Platform)
			{
				GameSettings::GetInstance()->GetSpawnManager()->platform->PlatfromAbilityUpdate();
			}
		}
		GameSettings::GetInstance()->GetSpawnManager()->DestroyObject(this);
}

