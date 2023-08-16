#pragma once
#include "SceneObject.h"
#include "vector2f.h"

class Ability : public SceneObject
{
public:
	Ability(Sprite* sprite, vector2f pos, float koef_, ObjectType affected_object_);

	void processCollision(SceneObject* sceneObj);

	void move();

	ObjectType GetObjectType() override;

	bool ChangeBallSize(SceneObject* sceneObj);
	bool ChangePlatformSize(SceneObject * sceneObj);

	void AbilityEnd();

protected:

	SceneObject* sceneObject;
	ObjectType affected_object;
	Sprite* affected_sprite;
	bool activated = false;
	float koef;
	float time = 20;
	float fall_speed = 0.5;
};