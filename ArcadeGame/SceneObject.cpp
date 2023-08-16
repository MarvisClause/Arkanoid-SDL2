#include"SceneObject.h"
#include"GameSettings.h"
#include"SpriteManager.h"

#include<cmath>

SceneObject::SceneObject(Sprite* sprite)
{
	this->sprite = sprite;

	if (GameSettings* settings = GameSettings::GetInstance())
	{
		if (SpriteManager* spriteManager = settings->GetSpriteManager())
		{
			spriteManager->getSpriteSize(sprite, sprite_w, sprite_h);
		}
	}
}

bool SceneObject::updateCollision(SceneObject* sceneObj) 
{
	if (sceneObj == this || sceneObj == nullptr)
	{
		return false;
	}

	float d = sqrtf((this->position.x - sceneObj->position.x) * (this->position.x - sceneObj->position.x)
		+ (this->position.y - sceneObj->position.y) * (this->position.y - sceneObj->position.y));
	if ((abs(this->position.x - sceneObj->position.x) < (this->sprite_w / 2 + sceneObj->sprite_w / 2))
		&& (abs(this->position.y - sceneObj->position.y) < (this->sprite_h / 2 + sceneObj->sprite_h / 2)))
	{

		this->processCollision(sceneObj);
		return true;
	}
	return false;
}

void SceneObject::SetCollisionBlock()
{
}

void SceneObject::SetPositon(vector2f pos)
{
	position = pos;
}

Sprite* SceneObject::GetSprite()
{
	return sprite;
}

int SceneObject::GetSpriteHeight()
{
	return sprite_h;
}

int SceneObject::GetSpriteWidth()
{
	return sprite_w;
}

vector2f SceneObject::GetPosition()
{
	return position;
}


