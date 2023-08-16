#pragma once

#include"SceneObject.h"

class DeathZone : public SceneObject
{
public:
	DeathZone(Sprite* sprite);

	void processCollision(SceneObject*);

	void move();

	ObjectType GetObjectType() override;

private:
};