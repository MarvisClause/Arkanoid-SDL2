#pragma once
#include "BaseObject.h"
#include "vector2f.h"
#include "ObjectType.h"

class Sprite;


class SceneObject : public BaseObject
{
public:

	SceneObject(Sprite* sprite);
	bool updateCollision(SceneObject* sceneObj);
	virtual void processCollision(SceneObject* sceneObj) = 0;
	virtual void SetCollisionBlock();
	virtual void SetPositon(vector2f pos);

	virtual void move() = 0;

	Sprite* GetSprite();
	int GetSpriteHeight();
	int GetSpriteWidth();
	vector2f GetPosition();

	virtual ObjectType GetObjectType() = 0;

protected:

	vector2f position;

	Sprite* sprite;
	int sprite_h;
	int sprite_w;
};