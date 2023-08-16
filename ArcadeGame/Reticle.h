#pragma once

#include "SceneObject.h"
#include "vector2f.h"

class Reticle : public SceneObject
{
public:
	Reticle(Sprite* sprite, vector2f start_pos);

	void move();

	void SetPosition(const int& x, const int& y);

	void processCollision(SceneObject* sceneObj);

	ObjectType GetObjectType() override;

private:

};