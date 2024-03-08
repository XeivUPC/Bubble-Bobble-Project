#pragma once
#include <raylib.h>
#include "VisualEntity.hpp"
#include "SystemCalls.hpp"
#include "TileMapData.hpp"
#include "LevelManager.hpp"

#include "GameManager.hpp"

class GameManager;

class Player : public VisualEntity
{

public:
	Player(GameManager* gameManager);
	void GetInput();
	void Move();
	void Jump();
	void CheckCollisions();
	void Update() override;
	void Render() override;
	void SetStatus(int index);
	void TpToSpawnPoint();
	void MoveToSpawnPoint();

	enum PlayerStatus
	{
		Playing,
		Dead,
		ChangingLevel
	};

	

private:
	PlayerStatus state = Playing;
	Texture2D playerTexture = LoadTexture("../Assets/Sprites/Player.png");
	GameManager* _gm;

	float xOffset=0;
	float yOffset=0;

	int _speed = 5;
	float _airSpeed =1.6;

	int _gravity=4;

	float _jumpInitialSpeed=7;
	float _jumpSpeed=7;
	float _jumpMaxSpeed=7;
	float _jumpHeight = 30 *5.1;
	float _jumpDistance = 0;
	float _jumpMovilityDebuff=25.f;

	Vector2 _direction;

	/////AnimationConstants
	const int WALK_FRAMES=5;
	const int WALK_THROW_FRAMES=4;
	const int IDLE_FRAMES=2;
	const int FALLING_FRAMES=2;
	const int JUMPING_FRAMES = 2;

	bool isGrounded=false;
	bool isJumping=false;
	bool isFalling=false;
	bool isMoving=false;
	bool isShooting = false;


	int bubbleState = 0;


	////Sounds
	Sound jumpSound = LoadSound("../Assets/Sounds/SFX/Jump.wav");
	Sound shootSound = LoadSound("../Assets/Sounds/SFX/Shoot.wav");
	
};