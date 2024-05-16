#include "Bubble.hpp"
#include "BubbleManager.hpp"
#include "LevelManager.hpp"
#include "TextureManager.hpp"
#include <math.h> 
#include <iostream>

Bubble::Bubble()
{
	Animation greenModeInertia = { TextureManager::Instance().GetTexture("BubbleTileSet"), 0.085f };
	greenModeInertia.frames.push_back({ 0 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	greenModeInertia.frames.push_back({ 1 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	greenModeInertia.frames.push_back({ 2 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	greenModeInertia.frames.push_back({ 3 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	greenModeInertia.frames.push_back({ 4 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	greenModeInertia.frames.push_back({ 5 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	Animation blueModeInertia = { TextureManager::Instance().GetTexture("BubbleTileSet") ,0.085f };
	blueModeInertia.frames.push_back({ 0 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	blueModeInertia.frames.push_back({ 1 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	blueModeInertia.frames.push_back({ 2 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	blueModeInertia.frames.push_back({ 3 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	blueModeInertia.frames.push_back({ 4 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	blueModeInertia.frames.push_back({ 5 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	


	Animation greenMode = { TextureManager::Instance().GetTexture("BubbleTileSet") ,4 };
	greenMode.frames.push_back({ 1 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	Animation blueMode = { TextureManager::Instance().GetTexture("BubbleTileSet") ,4 };
	blueMode.frames.push_back({ 10 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	Animation orangeMode = { TextureManager::Instance().GetTexture("BubbleTileSet") ,4 };
	orangeMode.frames.push_back({ 4 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	Animation redMode = { TextureManager::Instance().GetTexture("BubbleTileSet") ,4 };
	redMode.frames.push_back({ 7 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	Animation explode = { TextureManager::Instance().GetTexture("BubbleTileSet") ,0.2f };
	explode.frames.push_back({ 4 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	explode.frames.push_back({ 7 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	Animation pop = { TextureManager::Instance().GetTexture("BubbleTileSet") ,0.1f };
	pop.frames.push_back({ 2 * TILE_REAL_SIZE * 2,3 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	pop.frames.push_back({ 3 * TILE_REAL_SIZE * 2,3 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	

	renderer.AddAnimation("BubbleGreenInertiaMode", greenModeInertia);
	renderer.AddAnimation("BubbleBlueInertiaMode", blueModeInertia);
	renderer.AddAnimation("BubbleGreenMode", greenMode);
	renderer.AddAnimation("BubbleBlueMode", blueMode);
	renderer.AddAnimation("BubbleOrangeMode", orangeMode);
	renderer.AddAnimation("BubbleRedMode", redMode);
	renderer.AddAnimation("BubbleExplodeMode", explode);
	renderer.AddAnimation("BubblePop", pop);
	renderer.PlayAniamtion("BubbleGreenMode");
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{
	LevelManager& levelManager = LevelManager::Instance();
	int tileX;
	int tileY;
	if(enemyInside!=nullptr)
		internalTimer += deltaTime/2;
	else
		internalTimer += deltaTime;

	switch (state)
	{
	case Bubble::ShootInertia:
		if (internalTimer >= INERTIA_TIME)
		{
			internalTimer = 0;
			state = Idle;
		}

		position.x += (direction.x + directionOffset.x) * bubbleInertiaSpeed * TILE_SCALE_FACTOR * deltaTime;
		if (position.x < 2 * TILE_SIZE + TILE_SIZE)
		{
			position.x = 2 * TILE_SIZE + TILE_SIZE;
			if (state == ShootInertia){
				state = Idle;
				SetDirectionByTile();
			}
		}
		else if (position.x > (GAME_TILE_WIDTH - 2) * TILE_SIZE - TILE_SIZE) {
			position.x = (GAME_TILE_WIDTH - 2) * TILE_SIZE - TILE_SIZE;
			if (state == ShootInertia) {
				state = Idle;
				SetDirectionByTile();
			}
		}

		if (CheckEnemyCollisions()) {
			state = Idle;
			SetDirectionByTile();
		}

		break;
	case Bubble::Idle:
		if (internalTimer > LIFE_TIME) {
			Pop();	
			return;
		}

		if (enemyInside != nullptr)
			enemyInside->position = position;

		tileX = (int)(position.x / TILE_SIZE);
		tileY = (int)(position.y / TILE_SIZE);

		if (IsInTileCenter(Vector2{ (float)tileX, (float)tileY }, direction.x != 0) || (direction.x == 0 && direction.y == 0)) {
			SetDirectionByTile();
		}

		CheckCollisions();

		if (directionOffset.x != 0) {
			directionOffset.x += -directionOffset.x / abs(directionOffset.x) * 3 * deltaTime;
			if (abs(directionOffset.x) < 0.2)
				directionOffset.x = 0;
		}
		if (directionOffset.y != 0) {
			directionOffset.y += -directionOffset.y / abs(directionOffset.y) * 3 * deltaTime;
			if (abs(directionOffset.y) < 0.2)
				directionOffset.y = 0;
		}

		position.x += (direction.x + directionOffset.x) * bubbleSpeed * TILE_SCALE_FACTOR * deltaTime;
		if (position.x < 2 * TILE_SIZE + TILE_SIZE)
		{
			position.x = 2 * TILE_SIZE + TILE_SIZE;
			if (state == ShootInertia)
				state = Idle;
		}
		else if (position.x > (GAME_TILE_WIDTH - 2) * TILE_SIZE - TILE_SIZE) {
			position.x = (GAME_TILE_WIDTH - 2) * TILE_SIZE - TILE_SIZE;
			if (state == ShootInertia)
				state = Idle;
		}

		position.y += (direction.y + directionOffset.y) * bubbleSpeed * TILE_SCALE_FACTOR * deltaTime;

		if (enemyInside != nullptr) {
			enemyInside->SetBubbleTime(internalTimer);
		}

		break;
	default:
		break;
	}
	
	

}

void Bubble::Render()
{
	if (enemyInside != nullptr)\
		return;
	renderer.UpdateAnimation();
	if (state == ShootInertia) {
		isPlayer1Bubble ? renderer.PlayAniamtion("BubbleGreenInertiaMode") : renderer.PlayAniamtion("BubbleBlueInertiaMode");
	}
	else if (internalTimer < DEFAULT_BUBBLE_PHASE_TIME) {
		isPlayer1Bubble ? renderer.PlayAniamtion("BubbleGreenMode") : renderer.PlayAniamtion("BubbleBlueMode");
	}
	else if (internalTimer < ORANGE_BUBBLE_PHASE_TIME) {
		renderer.PlayAniamtion("BubbleOrangeMode");
	}
	else if (internalTimer < RED_BUBBLE_PHASE_TIME) {
		renderer.PlayAniamtion("BubbleRedMode");
	}
	else if (internalTimer > RED_BUBBLE_PHASE_TIME) {
		renderer.PlayAniamtion("BubbleExplodeMode");
	}
	
	renderer.Draw(position.x- TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
	
}

void Bubble::Debug() {
	DrawRectangleLines(position.x - TILE_SIZE, position.y - TILE_SIZE, TILE_SIZE * 2, TILE_SIZE * 2, GREEN);

	DrawCircleLines(position.x , position.y , TILE_SIZE/2.5f, RED);

	DrawCircle(position.x , position.y + TILE_SIZE/1.5f, TILE_SIZE/5, YELLOW);
	DrawCircle(position.x , position.y - TILE_SIZE / 1.5f, TILE_SIZE / 5, YELLOW);
	DrawCircle(position.x + TILE_SIZE / 1.5f, position.y , TILE_SIZE / 5, YELLOW);
	DrawCircle(position.x - TILE_SIZE / 1.5f, position.y , TILE_SIZE / 5, YELLOW);

	DrawCircle(position.x, position.y, TILE_SIZE / 5, RED);

	Rectangle collision = GetJumpCollision();
	DrawRectangle(collision.x, collision.y, collision.width, collision.height, { 0,0,255,100});

	collision = GetLeftCollision();
	DrawRectangle(collision.x, collision.y, collision.width, collision.height, { 255,255,0,100 });

	collision = GetRightCollision();
	DrawRectangle(collision.x, collision.y, collision.width, collision.height, { 255,255,0,100 });

	collision = GetBottomCollision();
	DrawRectangle(collision.x, collision.y, collision.width, collision.height, { 255,255,0,100 });

}

void Bubble::Reset()
{
	
	isActive = false;
	internalTimer = 0;
	direction = { 0,0 };
	directionOffset = { 0,0 };
	state = ShootInertia;
	if (enemyInside != nullptr) {
		enemyInside->RemoveFromBubble();
		enemyInside = nullptr;
	}
	enemyInside = nullptr;
}

void Bubble::Pop()
{	if(state==Idle)
		ParticleManager::Instance().AddParticle(new BubbleExplodeParticle(position));
	Reset();
}

bool Bubble::IsInTileCenter(Vector2 tileMatrixPos, bool isAxisX)
{
	float posTile = tileMatrixPos.x * TILE_SIZE + TILE_SIZE / 2;
	float distance = abs(position.x - posTile);
	if (!isAxisX) {
		posTile = tileMatrixPos.y * TILE_SIZE + TILE_SIZE / 2;
		distance = abs(position.y - posTile);
	}
	float range = 2 * TILE_SCALE_FACTOR;
	
	return distance <= range;
}

void Bubble::SetPlayerPosession(bool isPlayer1)
{
	isPlayer1Bubble = isPlayer1;
}

Rectangle Bubble::GetJumpCollision()
{
	Rectangle collision = { position.x - TILE_SIZE*0.7, position.y - TILE_SIZE, TILE_SIZE*1.4, TILE_SIZE / 1.5 };
	return collision;
}

Rectangle Bubble::GetRightCollision()
{
	Rectangle collision = { position.x + TILE_SIZE - TILE_SIZE / 1.5, position.y - TILE_SIZE * 0.7f, TILE_SIZE / 1.5f, TILE_SIZE * 1.4 };
	return collision;
}

Rectangle Bubble::GetLeftCollision()
{
	Rectangle collision = { position.x - TILE_SIZE, position.y - TILE_SIZE * 0.7f, TILE_SIZE / 1.5f, TILE_SIZE * 1.4 };
	return collision;
}

Rectangle Bubble::GetBottomCollision()
{
	Rectangle collision = { position.x - TILE_SIZE * 0.7, position.y + TILE_SIZE - TILE_SIZE / 1.5, TILE_SIZE * 1.4, TILE_SIZE / 1.5 };
	return collision;
}

Rectangle Bubble::GetKillCollision()
{
	Rectangle collision = { position.x - TILE_SIZE, position.y - TILE_SIZE, TILE_SIZE * 2, TILE_SIZE * 2 };
	return collision;
}

int Bubble::GetState()
{
	return state;
}

bool Bubble::KillEnemyInside(int* points)
{
	if (enemyInside != nullptr) {
		enemyInside->isActive=false;
		enemyInside->RemoveFromBubble();
		*points = enemyInside->GetPoints();
		enemyInside = nullptr;
		return true;
	}
	*points = 0;
	enemyInside = nullptr;
	return false;
}

void Bubble::SetDirectionOffset(Vector2 offset)
{
	directionOffset.x = offset.x;
	directionOffset.y = offset.y;
}

void Bubble::CheckCollisions()
{
	if (directionOffset.x!=0 || directionOffset.y!=0)
	{

	}
	else {
		BubbleManager& bubbleManager = BubbleManager::Instance();
		for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
		{
			Bubble* bubble = bubbleManager.GetBubbleByIndex(i);
			if (!bubble->isActive || directionOffset.x != 0 || directionOffset.y != 0 || bubble->state==ShootInertia || bubble == this)
				continue;
			Vector2 redCenter = { position.x , position.y };
			Vector2 otherRedCenter = { bubble->position.x , bubble->position.y };
			float RedRadius = TILE_SIZE / 2.5f;

			Vector2 topCenter = { bubble->position.x ,  bubble->position.y - TILE_SIZE / 1.5f };
			Vector2 leftCenter = { bubble->position.x ,  bubble->position.y + TILE_SIZE / 1.5f };
			Vector2 rightCenter = { bubble->position.x + TILE_SIZE / 1.5f,  bubble->position.y };
			Vector2 bottomCenter = { bubble->position.x - TILE_SIZE / 1.5f,  bubble->position.y };
			float yellowRadius = TILE_SIZE / 5;

			int randomPreSelection = rand() % 2;
			int randomReDirection = rand() % 2;
			if (CheckCollisionCircles(redCenter, RedRadius, otherRedCenter, RedRadius)) {


				if (randomPreSelection) {
					bubble->directionOffset.x = (rand() % 2 ? 1 : -1) * 1.5;
					bubble->directionOffset.y = direction.y * 3;
				}
				else {
					directionOffset.x = (rand() % 2 ? 1 : -1) * 1.5;
					directionOffset.y = bubble->direction.y * 1.5;
				}
			}
			else if (CheckCollisionCircles(redCenter, RedRadius, topCenter, yellowRadius) || CheckCollisionCircles(redCenter, RedRadius, bottomCenter, yellowRadius)) {
				if (randomPreSelection) {
					if (randomReDirection)
						bubble->directionOffset.y = -bubble->direction.y * 1.5;
					else
						bubble->directionOffset.y = direction.y * 1.5;
				}
				else {
					if (randomReDirection)
						directionOffset.y = -direction.y * 1.5;
					else
						directionOffset.y = bubble->direction.y * 1.5;

				}

			}
			else if (CheckCollisionCircles(redCenter, RedRadius, leftCenter, yellowRadius) || CheckCollisionCircles(redCenter, RedRadius, rightCenter, yellowRadius)) {
				if (randomPreSelection) {
					if (randomReDirection)
						bubble->directionOffset.x = -bubble->direction.x * 1.5;
					else
						bubble->directionOffset.x = direction.x * 1.5;
				}
				else {
					if (randomReDirection)
						directionOffset.x = -direction.x * 1.5;
					else
						directionOffset.x = bubble->direction.x * 1.5;

				}
			}
		}
	}

	///// Map Collisions

	Vector2 topCenter = { position.x ,  position.y - TILE_SIZE / 1.5f };
	Vector2 leftCenter = {position.x , position.y + TILE_SIZE / 1.5f };
	Vector2 rightCenter = { position.x + TILE_SIZE / 1.5f,  position.y };
	Vector2 bottomCenter = {position.x - TILE_SIZE / 1.5f, position.y };
	float yellowRadius = TILE_SIZE / 5;

	LevelManager& levelManager = LevelManager::Instance();
	Level& level = *levelManager.GetActiveLevel();


	float tileX = (int)(topCenter.x / TILE_SIZE);
	float tileY = (int)(topCenter.y / TILE_SIZE);
	int tileType = level.GetTile(tileX, tileY, level.GetCollisionsTilemap());
	Rectangle tileCollisison = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE, TILE_SIZE };
	//DrawRectangle(tileCollisison.x, tileCollisison.y, tileCollisison.width, tileCollisison.height, RED);
	if (tileType == 3 && CheckCollisionCircleRec(topCenter,yellowRadius, tileCollisison)) {
		position.y += abs((topCenter.y-yellowRadius)-(tileCollisison.y + tileCollisison.height));
		directionOffset.y = 0;
	}

	tileX = (int)(bottomCenter.x / TILE_SIZE);
	tileY = (int)(bottomCenter.y / TILE_SIZE);
	tileType = level.GetTile(tileX, tileY, level.GetCollisionsTilemap());
	tileCollisison = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE, TILE_SIZE };
	//DrawRectangle(tileCollisison.x, tileCollisison.y, tileCollisison.width, tileCollisison.height, WHITE);
	if (tileType == 3 && CheckCollisionCircleRec(bottomCenter, yellowRadius, tileCollisison)) {
		position.y -= abs((tileCollisison.y + tileCollisison.height) - (bottomCenter.y+yellowRadius));
		directionOffset.y = 0;
	}

	tileX = (int)(leftCenter.x / TILE_SIZE);
	tileY = (int)(leftCenter.y / TILE_SIZE);
	tileType = level.GetTile(tileX, tileY, level.GetCollisionsTilemap());
	tileCollisison = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE, TILE_SIZE };
	//DrawRectangle(tileCollisison.x, tileCollisison.y, tileCollisison.width, tileCollisison.height, BLUE);
	if (tileType == 3 && CheckCollisionCircleRec(leftCenter, yellowRadius, tileCollisison)) {
		position.x += abs((leftCenter.x - yellowRadius) - (tileCollisison.x + tileCollisison.width));
		directionOffset.x = 0;
	}

	tileX = (int)(rightCenter.x / TILE_SIZE);
	tileY = (int)(rightCenter.y / TILE_SIZE);
	tileType = level.GetTile(tileX, tileY, level.GetCollisionsTilemap());
	tileCollisison = { tileX * TILE_SIZE, tileY * TILE_SIZE,TILE_SIZE, TILE_SIZE };
	//DrawRectangle(tileCollisison.x, tileCollisison.y, tileCollisison.width, tileCollisison.height, YELLOW);
	if (tileType == 3 && CheckCollisionCircleRec(rightCenter, yellowRadius, tileCollisison)) {
		position.x -= abs((tileCollisison.x + tileCollisison.width) - (rightCenter.x + yellowRadius));
		directionOffset.x = 0;
	}

}

void Bubble::SetDirectionByTile()
{
	int tileX = (int)(position.x / TILE_SIZE);
	int tileY = (int)(position.y / TILE_SIZE);
	LevelManager& levelManager = LevelManager::Instance();
	int tileValues = levelManager.GetActiveLevel()->GetTile(tileX, tileY, levelManager.GetActiveLevel()->GetDirectionsTilemap());
	switch (tileValues)
	{
	case 1:
		direction.x = 0;
		direction.y = -1;
		break;
	case 2:
		direction.x = 0;
		direction.y = 1;
		break;
	case 3:
		direction.y = 0;
		direction.x = -1;
		break;
	case 4:
		direction.y = 0;
		direction.x = 1;
		break;
	default:
		direction.x = 0;
		direction.y = 0;
		break;
	}
}

bool Bubble::CheckEnemyCollisions()
{
	if (enemyInside != nullptr)
		return false;

	EnemyManager& manager = EnemyManager::Instance();
	for (size_t i = 0; i < manager.enemies.size(); i++)
	{
		if (manager.enemies[i]->isActive && !manager.enemies[i]->IsInsideBubble()) {
			Rectangle enemyCollision = manager.enemies[i]->GetCollider();
			if (CheckCollisionCircleRec(position, TILE_SIZE / 2.5f, enemyCollision)) {

				enemyInside = manager.enemies[i];
				enemyInside->TryToBubble(isPlayer1Bubble);
				return true;
			}
		}
	}
	return false;
}
