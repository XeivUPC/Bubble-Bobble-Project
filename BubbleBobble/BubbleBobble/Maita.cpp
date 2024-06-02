#include "Maita.hpp"
#include "TextureManager.hpp"
#include "EnemyManager.hpp"
#include "LevelManager.hpp"
#include "GameConfiguration.h"


Maita::Maita(Vector2 tilePos, int lookAt)
{
	position = tilePos;
	walkSpeed = TILE_SIZE * 6.f;
	walkAngrySpeed = walkSpeed * 2;
	direction.x = lookAt;
	internalTimer = MAITA_IA_RECALCULATION_TIME;
	pointsToGive = 1000;

	if (direction.x < 0) {
		renderer.FlipX(true);
	}
	if (direction.x > 0) {
		renderer.FlipX(false);
	}

	TextureManager::Instance().CreateTexture("Assets/Sprites/Enemy3.png", "MaitaSpriteSheet");

	Animation walkAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.12f };
	walkAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation idleAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.24f };
	idleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	idleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation walkAngryAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.06f };
	walkAngryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation idleAngryAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.12f };
	idleAngryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	idleAngryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 2 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	///

	Animation greenBubbleAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.2f };
	greenBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	greenBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	greenBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation blueBubbleAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.2f };
	blueBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 8 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	blueBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 8 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	blueBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 8 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation orangeBubbleAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.2f };
	orangeBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 9 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	orangeBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 9 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	orangeBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 9 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation redBubbleAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.2f };
	redBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 10 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	redBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 10 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	redBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 10 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation explodeBubbleAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.1f };
	explodeBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 9 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 10 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 9 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 10 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 9 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 10 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	///

	Animation throwAnim = { TextureManager::Instance().GetTexture("MaitaSpriteSheet") ,0.06f };
	throwAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	throwAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	throwAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	throwAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });


	renderer.AddAnimation("MaitaWalk", walkAnim);
	renderer.AddAnimation("MaitaIdle", idleAnim);
	renderer.AddAnimation("MaitaWalkAngry", walkAngryAnim);
	renderer.AddAnimation("MaitaIdleAngry", idleAngryAnim);

	///

	renderer.AddAnimation("MaitaGreenBubble", greenBubbleAnim);
	renderer.AddAnimation("MaitaBlueBubble", blueBubbleAnim);
	renderer.AddAnimation("MaitaOrangeBubble", orangeBubbleAnim);
	renderer.AddAnimation("MaitaRedBubble", redBubbleAnim);
	renderer.AddAnimation("MaitaExplodeBubble", explodeBubbleAnim);

	///

	renderer.AddAnimation("MaitaThrow", throwAnim);
}

Maita::~Maita()
{
}

void Maita::Update()
{
	if (isInsideBubble)
		return;

	retargetTimer += deltaTime;
	internalTimer += deltaTime;

	SearchTargetTile();

	Brain();

	if (currentTarget == nullptr)
		return;

	CheckCollisions();

	if (direction.x < 0) {
		renderer.FlipX(true);
	}
	if (direction.x > 0) {
		renderer.FlipX(false);
	}



	if (isClimbing) {
		speed.x = 0;
		speed.y = climbSpeed;
	}
	else {
		speed.x = isAngry ? walkAngrySpeed : walkSpeed;
		speed.y = gravity;
	}

	position.x += direction.x * speed.x * deltaTime;
	position.y += direction.y * speed.y * deltaTime;


	if (position.y > (GAME_TILE_HEIGHT + 1.5) * TILE_SIZE)
		position.y = 0;

}

void Maita::Render()
{
	renderer.UpdateAnimation();

	if (isInsideBubble)
	{
		if (bubbleTime < 10) {
			player1Bubble ? renderer.PlayAniamtion("MaitaGreenBubble") : renderer.PlayAniamtion("MaitaBlueBubble");
		}
		else if (bubbleTime < 13) {
			renderer.PlayAniamtion("MaitaOrangeBubble");
		}
		else if (bubbleTime < 14) {
			renderer.PlayAniamtion("MaitaRedBubble");
		}
		else if (bubbleTime > 14) {
			renderer.PlayAniamtion("MaitaExplodeBubble");
		}

		renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
	}
	else {
		if (direction.x == 0 && direction.y == 0) {
			if (isAngry) {
				renderer.PlayAniamtion("MaitaIdleAngry");
			}
			else {
				renderer.PlayAniamtion("MaitaIdle");
			}
		}
		else {
			if (isAngry) {
				renderer.PlayAniamtion("MaitaWalkAngry");
			}
			else {
				renderer.PlayAniamtion("MaitaWalk");
			}
		}
		renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE * 2, 0, WHITE);
	}




}

void Maita::Brain()
{
	if (isClimbing) {
		if (position.y < climbPoint) {
			isClimbing = false;

			position.y = climbPoint;
			if (needsToGoUp) {
				internalTimer = MAITA_IA_RECALCULATION_TIME - 0.7f;
				isWaitingClimbing = true;

			}
			else {
				if (needsToGoLeft) {
					direction.x = -1;
				}
				else {
					direction.x = 1;
				}
			}
			direction.y = 0;
		}
	}
	else if (isGoingDown && isGrounded) {
		isGoingDown = false;
		direction.y = 0;
		if (needsToGoLeft) {
			direction.x = -1;

		}
		else {
			direction.x = 1;

		}
	}
	else if (!isGoingDown && direction.x == 0 && !isWaitingClimbing && !isClimbing) {
		if (needsToGoLeft) {
			direction.x = -1;

		}
		else {
			direction.x = 1;

		}
	}

	if (needsToGoDown && !isGrounded && !isClimbing && !isWaitingClimbing && !isGoingDown) {

		internalTimer = MAITA_IA_RECALCULATION_TIME;
	}

	if (currentTarget == nullptr)
		return;

	if (MAITA_IA_RECALCULATION_TIME > internalTimer) {
		return;
	}
	isWaitingClimbing = false;
	if (currentTarget->position.y <= position.y - TILE_SIZE * 4) {
		needsToGoUp = true;
		needsToGoDown = false;
	}
	else {
		needsToGoUp = false;
		if (currentTarget->position.y >= position.y + TILE_SIZE * 4) {
			needsToGoDown = true;
		}
	}
	if (currentTarget->position.x <= position.x) {
		needsToGoLeft = true;
	}
	else {
		needsToGoLeft = false;
	}

	if (canGoUp && needsToGoUp && isGrounded) {
		direction.x = 0;
		direction.y = -1;
		climbPoint = position.y - 5 * TILE_SIZE;
		isClimbing = true;
		internalTimer = 0;
	}
	else if (needsToGoDown && !isGrounded)
	{
		direction.y = 1;
		direction.x = 0;
		internalTimer = 0;
		isGoingDown = true;
	}


}


void Maita::CheckCollisions()
{
	///Colliders
	Vector2 frontCheck = { position.x + TILE_SIZE * renderer.GetFlippedXValue(),position.y - TILE_SIZE };
	Vector2 topCheck = { position.x , position.y - (4.5 * TILE_SIZE) };
	Vector2 groundCheck = { position.x + TILE_SIZE * renderer.GetFlippedXValue(), position.y + TILE_SIZE / 2 };

	Vector2 groundedCheckRight = { position.x + (TILE_SIZE / 1.2), position.y };
	Vector2 groundedCheckLeft = { position.x - (TILE_SIZE / 1.2), position.y };

	Level& level = *LevelManager::Instance().GetActiveLevel();



	float tileX = (int)(frontCheck.x / TILE_SIZE);
	float tileY = (int)(frontCheck.y / TILE_SIZE);
	Rectangle tileCollision = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE,TILE_SIZE };
	if (CheckCollisionCircleRec(frontCheck, 1, tileCollision)) {
		if (level.GetTile(tileX, tileY, level.GetCollisionsTilemap()) == 2) {
			direction.x *= -1;
		}
	}

	tileX = (int)(groundCheck.x / TILE_SIZE);
	tileY = (int)(groundCheck.y / TILE_SIZE);
	tileCollision = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE,TILE_SIZE };
	if (CheckCollisionCircleRec(groundCheck, 1, tileCollision)) {
		if (level.GetTile(tileX, tileY, level.GetCollisionsTilemap()) == 0 && !needsToGoDown) {
			direction.x *= -1;
		}

	}

	tileX = (int)(topCheck.x / TILE_SIZE);
	tileY = (int)(topCheck.y / TILE_SIZE);
	tileCollision = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE,TILE_SIZE };
	if (CheckCollisionCircleRec(topCheck, 1, tileCollision)) {
		if (level.GetTile(tileX, tileY, level.GetCollisionsTilemap()) == 1) {
			canGoUp = true;
		}
		else {
			canGoUp = false;
		}
	}

	tileX = (int)(groundedCheckRight.x / TILE_SIZE);
	tileY = (int)(groundedCheckRight.y / TILE_SIZE);
	tileCollision = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE,TILE_SIZE };
	if (CheckCollisionCircleRec(groundedCheckRight, 1, tileCollision)) {
		if (level.GetTile(tileX, tileY, level.GetCollisionsTilemap()) == 0) {

			tileX = (int)(groundedCheckLeft.x / TILE_SIZE);
			tileY = (int)(groundedCheckLeft.y / TILE_SIZE);
			tileCollision = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE,TILE_SIZE };

			if (CheckCollisionCircleRec(groundedCheckLeft, 1, tileCollision)) {
				if (level.GetTile(tileX, tileY, level.GetCollisionsTilemap()) == 0) {
					isGrounded = false;

				}
				else {
					isGrounded = true;
				}
			}

		}
		else {
			isGrounded = true;
		}

	}

	if (position.y > (GAME_TILE_HEIGHT)*TILE_SIZE) {
		isGrounded = false;
	}

	Rectangle collision = { position.x - TILE_SIZE * 0.7, position.y - TILE_SIZE * 2 * 0.8, TILE_SIZE * 2 * 0.7, TILE_SIZE * 2 * 0.8 };
	for (size_t i = 0; i < EnemyManager::Instance().GetTargetsAmount(); i++)
	{
		Entity* x = EnemyManager::Instance().GetTarget(i);
		Player* player = dynamic_cast<Player*>(EnemyManager::Instance().GetTarget(i));
		if (player != nullptr && player->isActive) {

			if (CheckCollisionRecs(collision, player->GetCollision())) {
				player->HitPlayer();
			}
		}
	}

}

Rectangle Maita::GetCollider()
{
	Rectangle collider = { position.x - TILE_SIZE * 0.7, position.y - TILE_SIZE * 2 * 0.8, TILE_SIZE * 2 * 0.7, TILE_SIZE * 2 * 0.8 };
	return collider;
}

void Maita::Reset()
{
	position = { (float)((int)(position.x / TILE_SIZE)), (float)((int)(position.y / TILE_SIZE)) };
	position = { position.x * TILE_SIZE , position.y * TILE_SIZE };
	currentTarget = nullptr;
	retargetTimer = RETARGET_TIME;

	needsToGoUp = false;
	needsToGoDown = false;
	needsToGoLeft = false;

	canGoUp = false;
	canGoDown = false;

	isClimbing = false;
	isWaitingClimbing = false;
	isGoingDown = false;

	internalTimer = MAITA_IA_RECALCULATION_TIME;
	
	isGrounded = true;
	

	
	direction = { 0,1 };
	speed = { 0,0 };

	isInsideBubble = false;
	bubbleTime = 0;


}

void Maita::Debug()
{
	DrawCircle(position.x, position.y - (4.5 * TILE_SIZE), 0.1 * TILE_SIZE, BLUE); /// JumpVertical Debug
	DrawCircle(position.x, position.y - (3.5 * TILE_SIZE), 0.1 * TILE_SIZE, BLUE); /// JumpVertical Debug
	DrawCircle(position.x + TILE_SIZE * renderer.GetFlippedXValue(), position.y - TILE_SIZE, 0.1 * TILE_SIZE, RED); /// Wall Debug

	DrawCircle(position.x + TILE_SIZE * renderer.GetFlippedXValue(), position.y + TILE_SIZE / 2, 0.1 * TILE_SIZE, RED); /// Ground Debug

	DrawCircle(position.x - (TILE_SIZE / 1.2), position.y + 1, 0.1 * TILE_SIZE, GREEN);
	DrawCircle(position.x + TILE_SIZE / 1.2, position.y + 1, 0.1 * TILE_SIZE, GREEN);

	DrawRectangle(position.x - TILE_SIZE * 0.7, position.y - TILE_SIZE * 2 * 0.8, TILE_SIZE * 2 * 0.7, TILE_SIZE * 2 * 0.8, { 255,255,255,100 });

	if (currentTarget != nullptr)
		DrawLine(position.x, position.y, currentTarget->position.x, currentTarget->position.y, YELLOW);

}
