#include "CrackedBlock.h"
#include "GameSettings.h"

CrackedBlock::CrackedBlock(Sprite* sprite, vector2f pos) : SolidBlock(sprite, pos)
{

}

ObjectType CrackedBlock::GetObjectType()
{
	return ObjectType::Cracked_block;
}


