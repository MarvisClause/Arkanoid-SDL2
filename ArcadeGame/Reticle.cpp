#include "Reticle.h"

Reticle::Reticle(Sprite* sprite, vector2f start_pos) : SceneObject(sprite)
{
	position = start_pos;
}

void Reticle::move()
{

}

void Reticle::SetPosition(const int& x, const int& y)
{
	position.x = x;
	position.y = y;
}

void Reticle::processCollision(SceneObject* sceneObj)
{

}

ObjectType Reticle::GetObjectType()
{
	return ObjectType::Reticle;
}

