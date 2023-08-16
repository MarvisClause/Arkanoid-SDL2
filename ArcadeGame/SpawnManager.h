#pragma once
#include"BaseObject.h"
#include"ObjectType.h"
#include"SceneObject.h"
#include "SpriteManager.h"
#include<vector>

class MyFramework;
class Sprite;
class Platform;
class Reticle;
class Ball;
class SolidBlock;
class CrackedBlock;
class DeathZone;
class Ability;
class Turret;
class TurretBullet;

class SpawnManager : public BaseObject
{
public:

	SpawnManager(MyFramework* framework);

	std::vector<SceneObject*> GetSceneObjects();
	std::vector<SceneObject*> GetPlatformAbilities();
	std::vector<SceneObject*> GetBallAbilities();

	void CreateObj(ObjectType sprType_, Sprite* sprite);
	void DestroyObject(SceneObject* sceneObj);
	void SpawnBlocks();
	void FinishDeleting();
	void DestroyAllObjects();
	void CreateCrackedBlock(Sprite* sprite, vector2f position);
	void GenerateAbility(vector2f position);
	SceneObject* CreatePlatform(Sprite* sprite, vector2f position);
	int GetBallsAmount();
	int GetBlocksAmount();
	SceneObject* CreateAbility(SpriteTypes type, vector2f pos, float koef, ObjectType affected_object);
	void PushBackPlatformAbility(SceneObject* ability);
	void PushBackBallAbility(SceneObject* ability);

	std::vector<SceneObject*>GetBlocks();
	void SetBlockCollisionFalse();
	bool CheckAbilitySpawn();

	Platform* platform;
	Reticle* reticle;
	Turret* turret;
	TurretBullet* turret_bullet;
	SolidBlock* solidBlock;
	CrackedBlock* crackedBlock;
	DeathZone* deathZone;
	Ability* ability;

private:

	std::vector<SceneObject*>sceneObjects;
	std::vector<SceneObject*>objectsToDelete;
	std::vector<SceneObject*>balls;
	std::vector<SceneObject*>blocks;
	std::vector<SceneObject*>ball_abilities;
	std::vector<SceneObject*>platform_abilities;

	void CreateReticle(Sprite* sprite);

	void CreateBall(Sprite* sprite);

	void CreateSolidBlock(Sprite* sprite,vector2f position);

	bool isBlocked(vector2f position, int sprite_w, int sprite_h);

	MyFramework* framework;
};