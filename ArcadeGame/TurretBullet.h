#pragma once

#include"SceneObject.h"
#include"vector2f.h"

class TurretBullet : public SceneObject
{
public:
	TurretBullet(Sprite* sprite);

	void processCollision(SceneObject* sceneObj);

	void move();

	ObjectType GetObjectType();

private:

	vector2f direction;
};