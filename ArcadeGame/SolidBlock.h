#pragma once
#include "SceneObject.h"
#include "vector2f.h"

class SolidBlock : public SceneObject
{
public:
	SolidBlock(Sprite* sprite, vector2f pos);

	void processCollision(SceneObject* sceneObj);

	void move();

	ObjectType GetObjectType() override;

	bool isBottomLine();
	bool isBlockOnTop();

protected:
	
};

