#pragma once
#include "Entity.hpp"
#include "TilemapConfiguration.h"
#include "GameConfiguration.h"
#include "AnimationRenderer.hpp"


#define LIFE_TIME 16
#define INERTIA_TIME 0.4

#define DEFAULT_BUBBLE_PHASE_TIME 10
#define ORANGE_BUBBLE_PHASE_TIME 13
#define RED_BUBBLE_PHASE_TIME 14
#define EXPLODING_BUBBLE_PHASE_TIME 15

class Bubble : public Entity
{
public:
	Bubble();
	~Bubble();
	void Update() override;
	void Render() override;
	void Debug() override;
	bool IsInTileCenter(Vector2 tileMatrixPos, bool isAxisX);
	void SetPlayerPosession(bool isPlayer1);
private:
	
	enum BubbleState
	{
		ShootInertia,
		Idle
	};
	BubbleState state = ShootInertia;
	void CheckCollisions();
	void SetDirectionByTile();
	float bubbleSpeed = 24;
	float bubbleInertiaSpeed = 16*10;
	bool hasPop=false;
	bool isPlayer1Bubble = true;
protected:
	//// Collisions Info
	Vector2 directionOffset = { 0,0 };
	AnimationRenderer renderer;
};
