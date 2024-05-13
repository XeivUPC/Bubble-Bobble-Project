#pragma once
#include "Entity.hpp"
#include "AnimationRenderer.hpp"
#include "PuntuationHolder.hpp"
#include "TilemapConfiguration.h"
#include "PlayerDeadParticle.hpp"
#include "PlayerConfuseParticle.hpp"

#define PLAYER_SHOOT_INTERVAL  0.5
#define PLAYER_SHOOT_ANIMATION  0.4

#define INMORTAL_TIME 2
#define INMORTAL_BLINK_TIME 0.1

#define DYING_TIME 1.5
#define DEAD_TIME 1
#define POP_TIME 0.5


#define BUBBLE_START_TIME 0.6
#define BUBBLE_HOLD_TIME 0.4
#define BUBBLE_POP_TIME 0.4

class Player : public Entity
{
public:

	struct Keys {
		KeyboardKey Jump;
		KeyboardKey Left;
		KeyboardKey Right;
		KeyboardKey Shoot;
	};

	enum PlayerState {
		Normal,
		Dying,
		Dead,
		Pop,
		Inmortal,

		///BubbleRelated
		StartBubble,
		HoldBubble,
		PopBubble
	};

	Player(Keys controlScheme, bool player1, PuntuationHolder* controllerPoints);
	~Player();
	
	void Update() override;
	void Render() override;
	void Debug() override;
	void SetState(int index);
	void TpToSpawnPoint();
	bool MoveToSpawnPoint();
	int GetLifes();
	void HitPlayer();
	void HitPlayer_GOD_MODE();
	void HitPlayer(int amount);
	void HitPlayer_GOD_MODE(int amount);
	bool CanBeHit();
	bool IsInBubbleMode();
	bool CanBeHit_GOD_MODE();
	void SetIfCanBeHitted(bool value);
	void SetIfCanBeHitted_GOD_MODE(bool value);

	Rectangle GetCollision();

	void Reset() override;

	PuntuationHolder* puntuationController;
private:

	void GetInput();
	void Shoot();
	void TryJump();
	void Jump();
	void Move();
	void CheckCollisions();

	PlayerState state = StartBubble;

	bool player1 = false;
	int lifes = 3;

	Vector2 spawnPoint = { 3,27 };
	Vector2 startPoint = { 3,27 };
	AnimationRenderer renderer;
	Keys controlScheme;

	float shootTimer = PLAYER_SHOOT_INTERVAL;
	float inmortalTimer = INMORTAL_TIME;
	float deadRelatedTimer = 0;
	float bubbleTimer = 0;

	Vector2 speed={0,0};
	////Speeds X
	float groundSpeed=TILE_SIZE*9.f;
	float glidingSpeed = TILE_SIZE * 2.5f;
	float jumpXSpeed = TILE_SIZE * 7.f;

	////Speeds Y
	float gravity =TILE_SIZE * 9.f;


	////Jump
	
	float jumpStartYPoint = 0;
	float jumpInitialSpeed = TILE_SIZE * 24.6;
	float jumpCurrentSpeed=0;
	float jumpHeight = TILE_SIZE * 5.1f;

	////States
	bool isGrounded=true;
	bool isShooting = false;
	bool isJumping = false;
	
	bool hasBeenHit = false;
	bool canBeHit = true;
	bool isInBubbleMode = false;


	bool canBeHit_GOD_MODE = true;

	int frameCount = 0;



};

