#pragma once
#include "Entity.hpp"
#include "Renderer.hpp"
#include "PuntuationHolder.hpp"
#include "TilemapConfiguration.h"

#define PLAYER_SHOOT_INTERVAL  0.5
#define PLAYER_SHOOT_ANIMATION  0.4

#define INMORTAL_TIME 2
#define INMORTAL_BLINK_TIME 0.1

#define DYING_TIME 1.5
#define DEAD_TIME 1
#define POP_TIME 0.5

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
		Inmortal
	};

	Player(Keys controlScheme, bool player1, PuntuationHolder* controllerPoints);
	~Player();
	
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void SetState(int index);
	void TpToSpawnPoint();
	bool MoveToSpawnPoint();
	int GetLifes();
	void HitPlayer();
	void HitPlayer(int amount);
	bool CanBeHit();
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

	PlayerState state = Normal;

	bool player1 = false;
	int lifes = 3;

	Vector2 spawnPoint = { 3,27 };
	Renderer renderer;
	Keys controlScheme;

	float shootTimer = PLAYER_SHOOT_INTERVAL;
	float inmortalTimer = INMORTAL_TIME;
	float deadRelatedTimer = 0;

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
	float jumpHeight = TILE_SIZE * 5.f;

	////States
	bool isGrounded=true;
	bool isShooting = false;
	bool isJumping = false;
	
	bool hasBeenHit = false;
	bool canBeHit = true;


	bool canBeHit_GOD_MODE = true;

	int frameCount = 0;



};

