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
	bool TryToBubble(bool player1bubble);
	void RemoveFromBubble();
	int Kill();
	virtual void Hit(int amountDamage);
	virtual bool TryKill();
	bool IsInsideBubble();
	void SetBubbleTime(float time);
	void virtual Brain();
	void virtual SearchTargetTile();
	void virtual CheckCollisions();
	Rectangle virtual GetCollider();
	bool isAngry = false;
	int GetPoints();
protected:
	void virtual DrawDebug();
	AnimationRenderer renderer;

	float walkSpeed;
	float walkAngrySpeed;

	Entity* currentTarget = nullptr;
	float retargetTimer = RETARGET_TIME;
	float pointsToGive = 100;

	bool isInsideBubble=false;
	bool canBeInsideBubble = true;
	float bubbleTime = 0;
	float player1Bubble = false;
	int lifes = 1;
};

