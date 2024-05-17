#include "ZenChan.hpp"
#include "TextureManager.hpp"
#include "EnemyManager.hpp"
#include "LevelManager.hpp"
#include "GameConfiguration.h"


ZenChan::ZenChan(Vector2 tilePos, int lookAt)
{
	position = tilePos;
	walkSpeed = TILE_SIZE * 6.f;
	walkAngrySpeed = walkSpeed * 2;
	direction.x = lookAt;
	internalTimer = ZENCHAN_IA_RECALCULATION_TIME;
	pointsToGive = 1000;

	if (direction.x < 0) {
		renderer.FlipX(true);
	}
	if (direction.x > 0) {
		renderer.FlipX(false);
	}

	TextureManager::Instance().CreateTexture("Assets/Sprites/Enemy1.png", "ZenChanSpriteSheet");

	Animation walkAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.12f };
	walkAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation idleAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.24f };
	idleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	idleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 0 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation walkAngryAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.06f };
	walkAngryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	walkAngryAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation idleAngryAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.12f };
	idleAngryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, -TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	idleAngryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 1 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	///

	Animation greenBubbleAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.2f };
	greenBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	greenBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	greenBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation blueBubbleAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.2f };
	blueBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	blueBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	blueBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation orangeBubbleAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.2f };
	orangeBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	orangeBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	orangeBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation redBubbleAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.2f };
	redBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	redBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	redBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	Animation explodeBubbleAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.1f };
	explodeBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	explodeBubbleAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });

	///

	Animation throwAnim = { TextureManager::Instance().GetTexture("ZenChanSpriteSheet") ,0.06f };
	throwAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 2, 3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	throwAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 2, 3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	throwAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 2, 3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	throwAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 2, 3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });


	renderer.AddAnimation("ZenChanWalk", walkAnim);
	renderer.AddAnimation("ZenChanIdle", idleAnim);
	renderer.AddAnimation("ZenChanWalkAngry", walkAngryAnim);
	renderer.AddAnimation("ZenChanIdleAngry", idleAngryAnim);

	///

	renderer.AddAnimation("ZenChanGreenBubble", greenBubbleAnim);
	renderer.AddAnimation("ZenChanBlueBubble", blueBubbleAnim);
	renderer.AddAnimation("ZenChanOrangeBubble", orangeBubbleAnim);
	renderer.AddAnimation("ZenChanRedBubble", redBubbleAnim);
	renderer.AddAnimation("ZenChanExplodeBubble", explodeBubbleAnim);

	///

	renderer.AddAnimation("ZenChanThrow", throwAnim);
}

ZenChan::~ZenChan()
{
}

void ZenChan::Update()
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

}

void ZenChan::Render()
{
	renderer.UpdateAnimation();

	if (isInsideBubble)
	{
		if (bubbleTime < 10) {
			player1Bubble ? renderer.PlayAniamtion("ZenChanGreenBubble") : renderer.PlayAniamtion("ZenChanBlueBubble");
		}
		else if (bubbleTime < 13) {
			renderer.PlayAniamtion("ZenChanOrangeBubble");
		}
		else if (bubbleTime < 14) {
			renderer.PlayAniamtion("ZenChanRedBubble");
		}
		else if (bubbleTime > 14) {
			renderer.PlayAniamtion("ZenChanExplodeBubble");
		}

		renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
	}
	else {
		if (direction.x == 0 && direction.y == 0) {
			if (isAngry) {
				renderer.PlayAniamtion("ZenChanIdleAngry");
			}
			else {
				renderer.PlayAniamtion("ZenChanIdle");
			}
		}
		else {
			if (isAngry) {
				renderer.PlayAniamtion("ZenChanWalkAngry");
			}
			else {
				renderer.PlayAniamtion("ZenChanWalk");
			}
		}
		renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE * 2, 0, WHITE);
	}
	
	

	
}

void ZenChan::Brain()
{
	if (isClimbing) {
		if (position.y < climbPoint) {
			isClimbing = false;

			position.y = climbPoint;
			if (needsToGoUp) {
				internalTimer = ZENCHAN_IA_RECALCULATION_TIME - 0.7f;
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
	else if(!isGoingDown && direction.x==0 && !isWaitingClimbing && !isClimbing) {
		if (needsToGoLeft) {
			direction.x = -1;

		}
		else {
			direction.x = 1;

		}
	}

	if (needsToGoDown && !isGrounded && !isClimbing && !isWaitingClimbing && !isGoingDown) {

		internalTimer = ZENCHAN_IA_RECALCULATION_TIME;
	}

	if (currentTarget == nullptr)
		return;

	if (ZENCHAN_IA_RECALCULATION_TIME > internalTimer) {
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

	if (canGoUp && needsToGoUp && isGrounded ) {
			direction.x = 0;
			direction.y = -1;
			climbPoint = position.y - 5 * TILE_SIZE;
			isClimbing = true;
			internalTimer = 0;
	}
	else if (needsToGoDown && !isGrounded )
	{
		direction.y = 1;
		direction.x = 0;
		internalTimer = 0;
		isGoingDown = true;
	}


}


void ZenChan::CheckCollisions()
{
	///Colliders
	Vector2 frontCheck = { position.x + TILE_SIZE * renderer.GetFlippedXValue(),position.y - TILE_SIZE};
	Vector2 topCheck = { position.x , position.y - (4.5 * TILE_SIZE) };
	Vector2 groundCheck = { position.x + TILE_SIZE * renderer.GetFlippedXValue(), position.y + TILE_SIZE/2 };

	Vector2 groundedCheckRight = { position.x + (TILE_SIZE / 1.2), position.y};
	Vector2 groundedCheckLeft = { position.x - (TILE_SIZE / 1.2), position.y};

	Level& level = *LevelManager::Instance().GetActiveLevel();
	


	float tileX = (int)(frontCheck.x / TILE_SIZE);
	float tileY = (int)(frontCheck.y / TILE_SIZE);
	Rectangle tileCollision = { tileX* TILE_SIZE, tileY* TILE_SIZE,TILE_SIZE,TILE_SIZE };
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
	if (CheckCollisionCircleRec(groundedCheckRight,1, tileCollision)) {
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

	Rectangle collision = { position.x - TILE_SIZE * 0.7, position.y - TILE_SIZE * 2 * 0.8, TILE_SIZE * 2 * 0.7, TILE_SIZE * 2 * 0.8 };
	for (size_t i = 0; i < EnemyManager::Instance().GetTargetsAmount(); i++)
	{
		Entity* x = EnemyManager::Instance().GetTarget(i);
		Player* player = dynamic_cast<Player*>(EnemyManager::Instance().GetTarget(i));
		if (player!=nullptr && player->isActive) {

			if (CheckCollisionRecs(collision, player->GetCollision())) {
				player->HitPlayer();
			}
		}
	}

}

Rectangle ZenChan::GetCollider()
{
	Rectangle collider = { position.x - TILE_SIZE * 0.7, position.y - TILE_SIZE * 2 * 0.8, TILE_SIZE * 2 * 0.7, TILE_SIZE * 2 * 0.8 };
	return collider;
}

void ZenChan::Reset()
{

	internalTimer = ZENCHAN_IA_RECALCULATION_TIME;

}

void ZenChan::Debug()
{
	DrawCircle(position.x , position.y - (4.5 * TILE_SIZE), 3, BLUE); /// JumpVertical Debug
	DrawCircle(position.x , position.y - (3.5 * TILE_SIZE), 3, BLUE); /// JumpVertical Debug
	DrawCircle(position.x + TILE_SIZE * renderer.GetFlippedXValue(), position.y - TILE_SIZE, 3, RED); /// Wall Debug

	DrawCircle(position.x + TILE_SIZE * renderer.GetFlippedXValue(), position.y + TILE_SIZE / 2, 3, RED); /// Ground Debug

	DrawCircle(position.x - (TILE_SIZE / 1.2), position.y + 1, 3, GREEN);
	DrawCircle(position.x + TILE_SIZE /1.2, position.y + 1, 3, GREEN);

	DrawRectangle(position.x - TILE_SIZE * 0.7, position.y - TILE_SIZE * 2 * 0.8, TILE_SIZE * 2 * 0.7, TILE_SIZE * 2 * 0.8, {255,255,255,100});

	if (currentTarget != nullptr)
		DrawLine(position.x, position.y, currentTarget->position.x, currentTarget->position.y, YELLOW);

}
