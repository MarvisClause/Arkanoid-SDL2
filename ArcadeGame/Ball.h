#pragma once
#include "SceneObject.h"
#include "vector2f.h"

class Ball : public SceneObject
{
public:
	Ball(Sprite* sprite, vector2f platform_pos, vector2f reticle_pos);
	
	void processCollision(SceneObject* sceneObj);

	void move();

	ObjectType GetObjectType()override;

	void SetCollisionBlock();

private:

	vector2f direction;
	bool collisionBlock = false;

	void changeBallDirection(SceneObject* sceneObj);
	void isWall();
};