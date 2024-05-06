#pragma once
#include "Entity.hpp"
#include "Player.hpp"
#include "AnimationRenderer.hpp"
#include "TilemapConfiguration.h"
#define RETARGET_TIME 4

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	void Update() override;
	void Render() override;
	void Debug() override;
	void Reset() override;
	void virtual Brain();
	void virtual SearchTargetTile();
	void virtual CheckCollisions();
	bool isAngry = false;
protected:
	void virtual DrawDebug();
	AnimationRenderer renderer;

	float walkSpeed;
	float walkAngrySpeed;

	float speed;
	Entity* currentTarget = nullptr;
	float retargetTimer = RETARGET_TIME;
};

