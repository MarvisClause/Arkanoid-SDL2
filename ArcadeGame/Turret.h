#pragma once

#include"SceneObject.h"
#include "vector2f.h"

class Turret : public SceneObject
{
public:

	Turret(Sprite* sprite);

	void processCollision(SceneObject* sceneObj);

	void move();

	ObjectType GetObjectType();

	void Shoot();

private:

	vector2f direction ={0.1,0.1};

	float shoot_time = 10;
	float change_dir_time = 0;

	void isWall();
	void RandDirection();
};