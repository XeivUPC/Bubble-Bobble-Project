#include "Player.hpp"
#include "TextureManager.hpp"
#include "GameConfiguration.h"
#include "AudioManager.hpp"
#include "LevelManager.hpp"
#include "BubbleManager.hpp"

Player::Player(Keys controlScheme, bool player1,PuntuationHolder* controllerPoints)
{
	this->controlScheme = controlScheme;
	this->player1 = player1;
	puntuationController = controllerPoints;
	
	const char* textureName;

	if (this->player1)
	{
		spawnPoint = { 3,27 };
		TextureManager::Instance().CreateTexture("../Assets/Sprites/Player.png", "Player1SpriteSheet");
		textureName = "Player1SpriteSheet";
		renderer.FlipX();
		startPoint = { 9,21 };
	}
	else
	{
		spawnPoint = { 29,27 };
		startPoint = { 23,21 };
		TextureManager::Instance().CreateTexture("../Assets/Sprites/Player2.png", "Player2SpriteSheet");
		textureName = "Player2SpriteSheet";
	}
	AudioManager::Instance().CreateSound("../Assets/Sounds/SFX/Jump.wav", "Jump");
	AudioManager::Instance().CreateSound("../Assets/Sounds/SFX/Shoot.wav", "ShootBubble");
	AudioManager::Instance().CreateSound("../Assets/Sounds/SFX/Death.wav", "Death");
	AudioManager::Instance().CreateSound("../Assets/Sounds/SFX/KillEnemy.wav", "KillEnemy");

	Animation walkAnim = { TextureManager::Instance().GetTexture(textureName) ,0.07f };
	walkAnim.frames.push_back({ 0 * TILE_REAL_SIZE*2, 0 * TILE_REAL_SIZE*2, TILE_REAL_SIZE*2, TILE_REAL_SIZE*2 });
	walkAnim.frames.push_back({ 1 * TILE_REAL_SIZE*2, 0 * TILE_REAL_SIZE*2, TILE_REAL_SIZE*2, TILE_REAL_SIZE*2 });
	walkAnim.frames.push_back({ 2 * TILE_REAL_SIZE*2, 0 * TILE_REAL_SIZE*2, TILE_REAL_SIZE*2, TILE_REAL_SIZE*2 });
	walkAnim.frames.push_back({ 3 * TILE_REAL_SIZE*2, 0 * TILE_REAL_SIZE*2, TILE_REAL_SIZE*2, TILE_REAL_SIZE*2 });
	walkAnim.frames.push_back({ 4 * TILE_REAL_SIZE*2, 0 * TILE_REAL_SIZE*2, TILE_REAL_SIZE*2, TILE_REAL_SIZE*2 });
	walkAnim.frames.push_back({ 5 * TILE_REAL_SIZE*2, 0 * TILE_REAL_SIZE*2, TILE_REAL_SIZE*2, TILE_REAL_SIZE*2 });

	Animation fallAnim = { TextureManager::Instance().GetTexture(textureName) ,0.2f };
	fallAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	fallAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation idleAnim = { TextureManager::Instance().GetTexture(textureName) ,0.2f };
	idleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	idleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation jumpAnim = { TextureManager::Instance().GetTexture(textureName) ,0.2f };
	jumpAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	jumpAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation shootStaticAnim = { TextureManager::Instance().GetTexture(textureName) ,0.07 };
	shootStaticAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	shootStaticAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	shootStaticAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	shootStaticAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation shootMoveAnim = { TextureManager::Instance().GetTexture(textureName) ,0.07 };
	shootMoveAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	shootMoveAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	shootMoveAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	shootMoveAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation dieAnim = { TextureManager::Instance().GetTexture(textureName) ,0.0625f };
	dieAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	dieAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	dieAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	dieAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation deadAnim = { TextureManager::Instance().GetTexture(textureName) ,0.0625f };
	deadAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	deadAnim.frames.push_back({ 5 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	deadAnim.frames.push_back({ 6 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	deadAnim.frames.push_back({ 7 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation bubbleStart = { TextureManager::Instance().GetTexture(textureName) ,0.1f };
	bubbleStart.frames.push_back({ 0 * TILE_REAL_SIZE * 4, 4 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubbleStart.frames.push_back({ 1 * TILE_REAL_SIZE * 4, 4 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubbleStart.frames.push_back({ 0 * TILE_REAL_SIZE * 4, 5 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubbleStart.frames.push_back({ 1 * TILE_REAL_SIZE * 4, 5 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubbleStart.frames.push_back({ 2 * TILE_REAL_SIZE * 4, 5 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubbleStart.frames.push_back({ 3 * TILE_REAL_SIZE * 4, 5 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });

	Animation bubbleHold = { TextureManager::Instance().GetTexture(textureName) ,0.2f };
	bubbleHold.frames.push_back({ 0 * TILE_REAL_SIZE * 4, 6 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubbleHold.frames.push_back({ 1 * TILE_REAL_SIZE * 4, 6 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	

	Animation bubblePop = { TextureManager::Instance().GetTexture(textureName) ,0.2f };
	bubblePop.frames.push_back({ 0 * TILE_REAL_SIZE * 4, 7 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	bubblePop.frames.push_back({ 1 * TILE_REAL_SIZE * 4, 7 * TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4, TILE_REAL_SIZE * 4 });
	


	renderer.AddAnimation("PlayerWalk",walkAnim);
	renderer.AddAnimation("PlayerIdle",idleAnim);
	renderer.AddAnimation("PlayerFall",fallAnim);
	renderer.AddAnimation("PlayerJump",jumpAnim);
	renderer.AddAnimation("PlayerDie",dieAnim);
	renderer.AddAnimation("PlayerStaticShoot",shootStaticAnim);
	renderer.AddAnimation("PlayerMovingShoot",shootMoveAnim);

	renderer.AddAnimation("PlayerDie", dieAnim);
	renderer.AddAnimation("PlayerDead", deadAnim);
	renderer.AddAnimation("PlayerBubbleStart", bubbleStart);
	renderer.AddAnimation("PlayerBubbleHold", bubbleHold);
	renderer.AddAnimation("PlayerBubblePop", bubblePop);

	position.x = startPoint.x * TILE_SIZE;
	position.y = startPoint.y * TILE_SIZE;
}

Player::~Player()
{

}

void Player::GetInput()
{

	if (!isJumping) {
		direction.x = 0;
		direction.y = 1;
	}
	else {
		direction.x = 0;
	}
	if (IsKeyDown(controlScheme.Left))
	{
		direction.x = -1; renderer.FlipX(false);
	}
	if (IsKeyDown(controlScheme.Right))
	{
		direction.x = 1; renderer.FlipX(true);
	}
	if (IsKeyPressed(controlScheme.Jump))
		TryJump();
	if (PLAYER_SHOOT_INTERVAL <= shootTimer){
		
		if (IsKeyPressed(controlScheme.Shoot)) {
			Shoot();
		}
	}
	else {
		if (PLAYER_SHOOT_ANIMATION <= shootTimer)
			isShooting = false;
		else
			isShooting = true;
	}

	if (isJumping)
		Jump();
}

void Player::Shoot()
{
	AudioManager::Instance().PlaySoundByName("ShootBubble");
	Vector2 bubbleSpawwnPoint = { position.x, position.y - TILE_SIZE };
	Bubble* bubble = BubbleManager::Instance().GetBubble();
	if (bubble != nullptr) {
		bubble->isActive = true;
		bubble->position = bubbleSpawwnPoint;
		shootTimer = 0;
		bubble->direction = { -(float)renderer.GetFlippedXValue(),0 };
		bubble->SetPlayerPosession(player1);
	}
}

void Player::TryJump()
{
	if (isGrounded || (direction.y>0 && bubbleJumpTimer < BUBBLE_JUMP_COYOTE)) {
		AudioManager::Instance().PlaySoundByName("Jump");
		isGrounded = false;
		isJumping = true;
		jumpCurrentSpeed = jumpInitialSpeed;
		jumpStartYPoint = position.y;
		direction.y = -1;
		bubbleJumpTimer = 0;
		if (direction.x != 0)
			speed.x = jumpXSpeed * direction.x;
		else
			speed.x = 0;

		frameCount = 0;
		Jump();
	}
}

void Player::Jump()
{
	if (direction.y == 1) {
		direction.y = 1;
		jumpCurrentSpeed += (TILE_SIZE * 36) * deltaTime;
		if (jumpStartYPoint < position.y || isGrounded) {
			isJumping = false;
		}
	}
	else {
		direction.y = -1;
		jumpCurrentSpeed -= TILE_SIZE * 60 * deltaTime;
		if (jumpCurrentSpeed <= 0)
		{
			direction.y = 1;
			jumpCurrentSpeed = 0;
		}
	}
	frameCount++;
}

void Player::Move()
{
	switch (state) {
		case Normal:
			if (isGrounded)
			{
				speed.x = groundSpeed;
				speed.y = 0;
			}
			else {
				if (isJumping) {

					if (direction.x != 0) {
						speed.x += direction.x * jumpXSpeed * 2 * deltaTime;
						if (speed.x > jumpXSpeed)
							speed.x = jumpXSpeed;
						if (speed.x < -jumpXSpeed)
							speed.x = -jumpXSpeed;
					}
					if (speed.x != 0)
						direction.x = speed.x / abs(speed.x);
					speed.y = jumpCurrentSpeed;
				}
				else {
					speed.x = glidingSpeed;
					speed.y = gravity;
				}
			}
			break;
		case Dying:
			direction.y = 1;
			direction.x = 0;
			speed.y = gravity;
			break;
		case Dead:
		
			break;
		case Pop:
		
			break;
		case Inmortal:
			if (isGrounded)
			{
				speed.x = groundSpeed;
				speed.y = 0;
			}
			else {
				if (isJumping) {

					if (direction.x != 0) {
						speed.x += direction.x * jumpXSpeed * 2 * deltaTime;
						if (speed.x > jumpXSpeed)
							speed.x = jumpXSpeed;
						if (speed.x < -jumpXSpeed)
							speed.x = -jumpXSpeed;
					}
					if (speed.x != 0)
						direction.x = speed.x / abs(speed.x);
					speed.y = jumpCurrentSpeed;
				}
				else {
					speed.x = glidingSpeed;
					speed.y = gravity;
				}
			}
			break;

		case StartBubble:
			direction.y = 0;
			direction.x = 0;
			break;
		case HoldBubble:
			direction.y = 0;
			direction.x = 0;
			break;
		case PopBubble:
			direction.y = 0;
			direction.x = 0;
			break;
		default:
			break;
	}


	CheckCollisions();
	position.x += direction.x  * abs(speed.x) * deltaTime;
	position.y += direction.y * abs(speed.y) * deltaTime;
}

void Player::CheckCollisions()
{

	Level& level = *LevelManager::Instance().GetActiveLevel();

	Rectangle PlayerCollisionBottom = { position.x - (TILE_SIZE) * 0.8, position.y, TILE_SIZE * 1.6, TILE_SIZE * 0.1 };
	Rectangle PlayerCollisionLeft = { position.x - (TILE_SIZE)-TILE_SIZE * 0.1, position.y - TILE_SIZE * 1.5, TILE_SIZE * 0.1 , TILE_SIZE * 1 };
	Rectangle PlayerCollisionLeftFull = { position.x - (TILE_SIZE) - TILE_SIZE * 0.1, position.y - TILE_SIZE * 2, TILE_SIZE * 0.1 , TILE_SIZE * 2 };
	Rectangle PlayerCollisionRight = { position.x + (TILE_SIZE), position.y - TILE_SIZE * 1.5, TILE_SIZE * 0.1 , TILE_SIZE * 1 };
	Rectangle PlayerCollisionRightFull = { position.x + (TILE_SIZE), position.y - TILE_SIZE * 2, TILE_SIZE * 0.1 , TILE_SIZE * 2 };
	Rectangle PlayerCollisionTop = { position.x - (TILE_SIZE) * 0.8, position.y - TILE_SIZE * 2, TILE_SIZE * 1.6, TILE_SIZE * 0.1 };

	int Offset = -TILE_SIZE * 0.1f;
	Rectangle PlayerCollision = { position.x - (TILE_SIZE) + Offset ,position.y - (TILE_SIZE * 2) + Offset, TILE_SIZE * 2 - Offset * 2, TILE_SIZE * 2 - Offset * 2 };

	int tileX = (float)floor(position.x) / TILE_SIZE;
	int tileY = (float)floor(position.y - TILE_SIZE / 2) / TILE_SIZE;

	isGrounded = false;
	bool isBarrier = false;
	bool checkMoreAxisX = true;
	bool checkMoreAxisY = true;

	Vector2 fixPosition = position;
	Vector2 fixDirection = direction;

	
	if (tileY < 1)
		return;

	for (int y = tileY - 3; y < tileY + 3; y++)
	{
		Vector2 yTilePosition = { y*TILE_SIZE ,TILE_SIZE };
		for (int x = tileX - 3; x < tileX + 3; x++)
		{
			if (level.IsTile(x, y, level.GetCollisionsTilemap())) {
				int tileValue = level.GetTile(x, y, level.GetCollisionsTilemap());
				if (tileValue == 3)
					continue;
				Vector2 xTilePosition = { x * TILE_SIZE, TILE_SIZE };
				Rectangle tileCollision{ xTilePosition.x, yTilePosition.x,xTilePosition.y,yTilePosition.y };

				if (CheckCollisionRecs(PlayerCollisionBottom, tileCollision) && checkMoreAxisY) {
					if (y > tileY && direction.y > 0 && ((position.y + TILE_SIZE / 2) - y * TILE_SIZE) <= TILE_SIZE / 1.4 && (tileValue==1 || tileValue == 2)) {
						fixDirection.y = 0;
						isGrounded = true;
						fixPosition.y = y * TILE_SIZE;
					}
					else
						isGrounded = false;
				}
				else {
					if (!isGrounded)
						isGrounded = false;
				}
				if (CheckCollisionRecs(PlayerCollision, tileCollision)) {
					if (tileValue == 2 || isBarrier) {
						isBarrier = true;
						checkMoreAxisX = true;
					}
					else {
						if (direction.y < 0) {
							checkMoreAxisX = false;
							fixDirection.x = direction.x;
							continue;
						}
						checkMoreAxisX = true;
					}
				}
				if (CheckCollisionRecs(PlayerCollisionTop, tileCollision) && tileValue == 2 || !checkMoreAxisY) {
					checkMoreAxisY = false;
					checkMoreAxisX = false;
					isGrounded = false;
					fixDirection.y = direction.y;
				}
				if (checkMoreAxisX ) {
					
					if (direction.x < 0 && CheckCollisionRecs(PlayerCollisionLeft, tileCollision)) {
						if (tileValue == 1 && direction.y < 0 && !isBarrier) {
							continue;
						}
						if (x < tileX) {
							fixDirection.x = 0;
							if (isBarrier && isJumping)
								speed.x = 0;
						}
					}
					if (direction.x > 0 && CheckCollisionRecs(PlayerCollisionRight, tileCollision)) {
						if (tileValue == 1 && direction.y < 0 && !isBarrier) {
							continue;
						}
						if (x > tileX) {
							fixDirection.x = 0;
							if (isBarrier && isJumping)
								speed.x = 0;
						}
					}
				}
			}
		}
	}

	direction = fixDirection;
	if (isGrounded) {
		isJumping = false;
		position.y = fixPosition.y;
	}

	//// Bubbles

	Rectangle BubbleKill = { position.x - (TILE_SIZE) * 0.6, position.y - TILE_SIZE * 1.6, TILE_SIZE * 1.4, TILE_SIZE * 1 };

	isOnBubble = false;
	BubbleManager& bubbleManager = BubbleManager::Instance();
	for (size_t i = 0; i < bubbleManager.GetBubbleAmount(); i++)
	{
		Bubble* bubble = bubbleManager.GetBubbleByIndex(i);
		if (bubble->isActive) {
			if (!isOnBubble) {
				if (CheckCollisionRecs(bubble->GetJumpCollision(), PlayerCollisionBottom)) {
					isOnBubble = true;
				}
			}
			if (bubble->GetState() == 1) {
				if (CheckCollisionRecs(bubble->GetKillCollision(), BubbleKill)) {
					int points = 0;
					if (bubble->KillEnemyInside(&points)) {
						puntuationController->ModifyPuntutation(points);
						AudioManager::Instance().PlaySoundByName("KillEnemy");
					}
					else {
						puntuationController->ModifyPuntutation(10);
					}
					bubble->Pop();
					
				}
				else
				{
					if (CheckCollisionRecs(bubble->GetLeftCollision(), PlayerCollisionRightFull)) {
						bubble->SetDirectionOffset({direction.x*3,0});
					}
					if (CheckCollisionRecs(bubble->GetRightCollision(), PlayerCollisionLeftFull)) {
						bubble->SetDirectionOffset({ direction.x*3,0 });
					}
					if (CheckCollisionRecs(bubble->GetBottomCollision(), PlayerCollisionTop)) {
						bubble->SetDirectionOffset({ 0,direction.y*4 });
					}

				}
			}
			
			
		}
	}
	
}




void Player::Update()
{
	internalTimer += deltaTime;
	
	if (LevelManager::Instance().IsOnTransition() && !isInBubbleMode) {
		isInBubbleMode = true;
		SetState(5);
	}
	
	switch (state) {
	case Normal:
		shootTimer += deltaTime;
		if (!isOnBubble)
			bubbleJumpTimer += deltaTime;
		else
			bubbleJumpTimer = 0;
		GetInput();
		Move();
		break;
	case Dying:
		deadRelatedTimer += deltaTime;
		Move();
		if (deadRelatedTimer >= DYING_TIME) {
			SetState(2);
		}
		break;
	case Dead:
		deadRelatedTimer += deltaTime;
		if (deadRelatedTimer >= DEAD_TIME) {
			SetState(3);
		}
		break;
	case Pop:
		deadRelatedTimer += deltaTime;
		if (deadRelatedTimer >= POP_TIME)
		{
			hasBeenHit = false;
			if (lifes < 0) {
				lifes = 3;
				isActive = false;
			}
			else {
				TpToSpawnPoint();
				SetState(4);
			}
		}
		break;
	case Inmortal:
		inmortalTimer += deltaTime;
		shootTimer += deltaTime;
		GetInput();
		Move();
		if (inmortalTimer >= INMORTAL_TIME) {
			canBeHit = true;
			renderer.isActive = true;
			SetState(0);
		}
		break;

	case StartBubble:
		bubbleTimer += deltaTime;
		MoveToSpawnPoint();
		if(bubbleTimer>= BUBBLE_START_TIME){
			SetState(6);
		}
		break;
	case HoldBubble:
		bubbleTimer += deltaTime;
		if (MoveToSpawnPoint() && bubbleTimer>= BUBBLE_HOLD_TIME && !LevelManager::Instance().IsOnTransition())
			SetState(7);
		break;
	case PopBubble:
		bubbleTimer += deltaTime;
		if (bubbleTimer >= BUBBLE_POP_TIME) {
			isGrounded = true;
			isInBubbleMode = false;
			direction.x = 0;
			direction.y = 0;
			isJumping = false;
			hasBeenHit = false;
			renderer.ChangeDisplacement({ 0,0});
			SetState(0);
		}
		break;
	default:
		break;
	}

	if (position.y > (GAME_TILE_HEIGHT + 1.5) * TILE_SIZE)
		position.y = 0;
}

void Player::Render()
{
	renderer.UpdateAnimation();
	if (!canBeHit || !canBeHit_GOD_MODE) {
		renderer.isActive = !renderer.isActive;
	}
	if (!renderer.isActive)
		return;

	if (state == StartBubble) {
		renderer.PlayAniamtion("PlayerBubbleStart");
	}
	else if (state == HoldBubble) {
		renderer.PlayAniamtion("PlayerBubbleHold");
	}
	else if (state == PopBubble) {
		renderer.PlayAniamtion("PlayerBubblePop");
	}
	else if (state == Dying) {
		renderer.PlayAniamtion("PlayerDie");
	}
	else if (state == Dead) {
		renderer.PlayAniamtion("PlayerDead");
	}
	else if (state == Pop) {
		return;
	}
	else if (state == Normal || state == Inmortal) {
		if (isShooting)
		{
			if (direction.x != 0)
				renderer.PlayAniamtion("PlayerMovingShoot");
			else
				renderer.PlayAniamtion("PlayerStaticShoot");
		}
		else if (isGrounded) {
			if (direction.x != 0)
				renderer.PlayAniamtion("PlayerWalk");
			else
				renderer.PlayAniamtion("PlayerIdle");
		}
		else {
			if (direction.y > 0) {
				renderer.PlayAniamtion("PlayerFall");
			}
			else {
				renderer.PlayAniamtion("PlayerJump");
			}
		}
	}
	

	
	
	renderer.Draw(position.x- TILE_SIZE, position.y - TILE_SIZE*2, 0, WHITE);
	
	
}

void Player::SetState(int index)
{
	state = static_cast<PlayerState>(index);

	switch (state) {
	case Normal:
		renderer.isActive = true;
		break;
	case Dying:
		AudioManager::Instance().PlaySoundByName("Death");
		hasBeenHit = true;
		deadRelatedTimer = 0;
		break;
	case Dead:
		deadRelatedTimer = 0;
		Vector2 confusePos = position;
		confusePos.y -= TILE_SIZE*2;
		ParticleManager::Instance().AddParticle(new PlayerConfuseParticle(confusePos));
		break;
	case Pop:
		deadRelatedTimer = 0;
		ParticleManager::Instance().AddParticle(new PlayerDeadParticle(position));

		renderer.FlipX(this->player1);

		break;
	case Inmortal:
		inmortalTimer = 0;
		canBeHit = false;
		break;

	case StartBubble:
		isShooting = false;
		isJumping = false;
		canBeHit = true;
		renderer.FlipX(player1);
		renderer.ChangeDisplacement({ -TILE_SIZE ,-TILE_SIZE });
		bubbleTimer = 0;
		break;
	case HoldBubble:
		bubbleTimer = 0;
		break;
	case PopBubble:
		bubbleTimer = 0;
		break;
	default:
		break;
	}
}

void Player::Debug() {
	DrawCircle(position.x, position.y, 4, BLUE);



	Rectangle PlayerCollisionBottom = { position.x - (TILE_SIZE) * 0.8, position.y, TILE_SIZE * 1.6, TILE_SIZE * 0.1 };
	Rectangle PlayerCollisionLeft = { position.x - (TILE_SIZE)-TILE_SIZE * 0.1, position.y - TILE_SIZE * 1.5, TILE_SIZE * 0.1 , TILE_SIZE * 1 };
	Rectangle PlayerCollisionRight = { position.x + (TILE_SIZE), position.y - TILE_SIZE * 1.5, TILE_SIZE * 0.1 , TILE_SIZE * 1 };

	Rectangle PlayerCollisionTop = { position.x - (TILE_SIZE) * 0.8, position.y - TILE_SIZE * 2, TILE_SIZE * 1.6, TILE_SIZE * 0.1 };

	Rectangle PlayerCollisionLeftFull = { position.x - (TILE_SIZE)-TILE_SIZE * 0.1, position.y - TILE_SIZE * 2, TILE_SIZE * 0.1 , TILE_SIZE * 2 };
	Rectangle PlayerCollisionRightFull = { position.x + (TILE_SIZE), position.y - TILE_SIZE * 2, TILE_SIZE * 0.1 , TILE_SIZE * 2 };

	DrawRectangle(PlayerCollisionLeftFull.x, PlayerCollisionLeftFull.y, PlayerCollisionLeftFull.width, PlayerCollisionLeftFull.height, GREEN);
	DrawRectangle(PlayerCollisionRightFull.x, PlayerCollisionRightFull.y, PlayerCollisionRightFull.width, PlayerCollisionRightFull.height, GREEN);

	DrawRectangle(PlayerCollisionBottom.x, PlayerCollisionBottom.y, PlayerCollisionBottom.width, PlayerCollisionBottom.height, RED);
	DrawRectangle(PlayerCollisionLeft.x, PlayerCollisionLeft.y, PlayerCollisionLeft.width, PlayerCollisionLeft.height, RED);
	DrawRectangle(PlayerCollisionRight.x, PlayerCollisionRight.y, PlayerCollisionRight.width, PlayerCollisionRight.height, RED);
	DrawRectangle(PlayerCollisionTop.x, PlayerCollisionTop.y, PlayerCollisionTop.width, PlayerCollisionTop.height, RED);

	DrawRectangle(position.x - TILE_SIZE, position.y - (TILE_SIZE * 2), TILE_SIZE * 2, TILE_SIZE * 2, { 255,255,255,100 });

	DrawRectangle(position.x - (TILE_SIZE) * 0.6, position.y - TILE_SIZE * 1.6, TILE_SIZE * 1.4, TILE_SIZE * 1, { 255,0,0,100 });
}

void Player::TpToSpawnPoint()
{
	position = { TILE_SIZE * spawnPoint.x ,TILE_SIZE * spawnPoint.y };
}

bool Player::MoveToSpawnPoint()
{
	bool arrived = true;

	Vector2 spawnPos = { TILE_SIZE * spawnPoint.x ,TILE_SIZE * spawnPoint.y };
	Vector2 moveDir = { (spawnPos.x - position.x) / abs(spawnPos.x - position.x),(spawnPos.y - position.y) / abs(spawnPos.y - position.y) };
	if (abs(spawnPos.x - position.x) > 0.2f) {
		position.x += moveDir.x * groundSpeed / 1.5f * deltaTime;
		arrived = false;
	}
	else {
		position.x = spawnPos.x;
	}
	if (abs(spawnPos.y - position.y) > 0.2f) {
		position.y += moveDir.y * groundSpeed/1.5f * deltaTime;
		arrived = false;
	}
	else {
		position.y = spawnPos.y;
	}
	return arrived;
}

int Player::GetLifes()
{
	return lifes;
}

void Player::HitPlayer()
{
	if (hasBeenHit || !canBeHit || !canBeHit_GOD_MODE)
		return;
	lifes--;
	SetState(1);
}

void Player::HitPlayer_GOD_MODE()
{
	lifes--;
	SetState(1);
}

void Player::HitPlayer(int amount)
{
	if (hasBeenHit || !canBeHit || !canBeHit_GOD_MODE)
		return;

	lifes-= amount;
	SetState(1);
}

void Player::HitPlayer_GOD_MODE(int amount)
{
	lifes -= amount;
	SetState(1);
}

bool Player::CanBeHit()
{
	return canBeHit;
}

bool Player::IsInBubbleMode()
{
	return isInBubbleMode;
}

bool Player::CanBeHit_GOD_MODE()
{
	return canBeHit_GOD_MODE;
}

void Player::SetIfCanBeHitted(bool value)
{
	canBeHit = value;
	if(canBeHit)
		renderer.isActive = true;
}

void Player::SetIfCanBeHitted_GOD_MODE(bool value)
{
	canBeHit_GOD_MODE = value;
	if (canBeHit_GOD_MODE)
		renderer.isActive = true;
}

Rectangle Player::GetCollision()
{
	return Rectangle({ position.x - TILE_SIZE, position.y - (TILE_SIZE * 2),  TILE_SIZE * 2, TILE_SIZE * 2});
}

void Player::Reset()
{
	lifes = 3;
	isActive = true;
	isInBubbleMode = true;
	position.x = startPoint.x * TILE_SIZE;
	position.y = startPoint.y * TILE_SIZE;
	renderer.isActive = true;
	canBeHit = true;
	SetState(5);
}


