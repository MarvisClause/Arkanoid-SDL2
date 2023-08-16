#pragma once

#include"SolidBlock.h"
#include"vector2f.h"

class CrackedBlock : public SolidBlock
{
public:
	using Parent = SolidBlock;

	CrackedBlock(Sprite* sprite, vector2f pos);

	ObjectType GetObjectType() override;

private:

};