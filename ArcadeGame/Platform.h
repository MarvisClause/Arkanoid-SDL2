#pragma once

#include "SceneObject.h"
#include<utility>

enum class FRKey;

class Platform : public SceneObject
{
public:
	Platform(Sprite* sprite);

	Platform(Sprite* sprite, vector2f pos);
	
	SceneObject* PlatfromAbilityUpdate();

	void processKeyPressed(FRKey k);

	void processKeyReleased(FRKey k);

	void processCollision(SceneObject* sceneObj);

	void move();

	ObjectType GetObjectType();

private:
	int movement = 0;

	bool isRightWall();

	bool isLeftWall();
};