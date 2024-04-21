#pragma once
#include "Entity.hpp"
#include "Player.hpp"
#include "Renderer.hpp"
#include "TilemapConfiguration.h"
#define RETARGET_TIME 4

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Reset() override;
	void virtual Brain();
	void virtual SearchTargetTile();
	void virtual CheckCollisions();
protected:
	void virtual DrawDebug();
	Renderer renderer;
	bool isAngry = false;

	float walkSpeed;
	float walkAngrySpeed;

	float speed;
	Entity* currentTarget = nullptr;
	float retargetTimer = RETARGET_TIME;
};

