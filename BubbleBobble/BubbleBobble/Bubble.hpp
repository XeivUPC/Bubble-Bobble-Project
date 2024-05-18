#pragma once
#include "Entity.hpp"
#include "EnemyManager.hpp"
#include "TilemapConfiguration.h"
#include "GameConfiguration.h"
#include "AnimationRenderer.hpp"
#include "BubbleExplodeParticle.hpp"
#include "ElectricThunderBoltParticle.hpp"


#define LIFE_TIME 15
#define INERTIA_TIME 0.4

#define DEFAULT_BUBBLE_PHASE_TIME 10
#define ORANGE_BUBBLE_PHASE_TIME 13
#define RED_BUBBLE_PHASE_TIME 14


class Bubble : public Entity
{
	friend class Player;
public:
	enum BubbleType {
		Default,
		Electric
	};
	Bubble();
	~Bubble();
	void Update() override;
	void Render() override;
	void Debug() override;
	void Reset() override;
	void Pop();
	void SetPopDirection(Vector2 popDirection);
	bool IsInTileCenter(Vector2 tileMatrixPos, bool isAxisX);
	void SetPlayerPosession(bool isPlayer1);
	Rectangle GetJumpCollision();
	Rectangle GetRightCollision();
	Rectangle GetLeftCollision();
	Rectangle GetBottomCollision();
	Rectangle GetKillCollision();
	int GetState();
	void SetBubbleType(BubbleType type);
	bool KillEnemyInside(int* points);
	void SetDirectionOffset(Vector2 offset);
private:
	
	enum BubbleState
	{
		ShootInertia,
		Idle
	};
	BubbleType type = Default;
	BubbleState state = ShootInertia;
	void CheckCollisions();
	void SetDirectionByTile();
	bool CheckEnemyCollisions();
	float bubbleSpeed = 20;
	float bubbleInertiaSpeed = 16*10;
	bool isPlayer1Bubble = true;
	Enemy* enemyInside = nullptr;
protected:
	//// Collisions Info
	Vector2 directionOffset = { 0,0 };
	AnimationRenderer renderer;
	Vector2 popDirection{ 1,0 };
};
