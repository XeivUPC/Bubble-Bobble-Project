#include "SuperDrunk.hpp"
#include "EnemyManager.hpp"

SuperDrunk::SuperDrunk(Vector2 tilePos, int lookAt) {
	position = {tilePos.x, tilePos.y+6*TILE_SIZE};
	spawnPoint = tilePos;
	direction = {1,-1};
	speed = TILE_SIZE * 7.f;
	lifes = 20;
	TextureManager::Instance().CreateTexture("Assets/Sprites/Boss.png", "SuperDrunkSpriteSheet");

	Animation normalAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	normalAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	normalAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	normalAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	normalAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

	Animation angryAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	angryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 1 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	angryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8, 1 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

	Animation deadAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	deadAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 2 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	deadAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

	Animation hitAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.1f };
	hitAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 2 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

	Animation dieAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	dieAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 2 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	dieAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8, 2 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	dieAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8, 2 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	dieAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 8, 2 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	
	Animation bubbleAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	bubbleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 3 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	bubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8, 3 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

	renderer.AddAnimation("SuperDrunkNormal", normalAnim);
	renderer.AddAnimation("SuperDrunkAngry", angryAnim);
	renderer.AddAnimation("SuperDrunkDie", dieAnim);
	renderer.AddAnimation("SuperDrunkHit", hitAnim);
	renderer.AddAnimation("SuperDrunkDead", deadAnim);
	renderer.AddAnimation("SuperDrunkBubble", bubbleAnim);

	renderer.PlayAniamtion("SuperDrunkNormal");
}

SuperDrunk::~SuperDrunk()
{

}

void SuperDrunk::Update()
{
	
	if (hasBeenHit) {
		internalTimer += deltaTime;
		if (internalTimer > HIT_RENDER)
			hasBeenHit = false;
	}
	CheckCollisions();

	if (lifes == 0) {
		if (MoveToSpawnPoint()) {
			direction.x = -1;
		}
	}
	else {
		position.x += direction.x * speed * deltaTime;
		position.y += direction.y * speed * deltaTime;
	}


}

void SuperDrunk::Render()
{
	if (direction.x > 0) {
		renderer.FlipX(false);
	}
	else {
		renderer.FlipX(true);
	}

	if (lifes == 0) {
		if(position.x != spawnPoint.x || position.y != spawnPoint.y)
			renderer.PlayAniamtion("SuperDrunkDead");
		else {
			renderer.PlayAniamtion("SuperDrunkBubble");
		}
	}
	else if (hasBeenHit) {
		renderer.PlayAniamtion("SuperDrunkHit");
	}
	else {
		renderer.PlayAniamtion("SuperDrunkNormal");
	}

	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE*4, position.y - TILE_SIZE * 8, 0, WHITE);
}

void SuperDrunk::Debug()
{
	Rectangle collider = GetCollider();
	DrawRectangle(collider.x, collider.y, collider.width, collider.height, { 255,255,255,100 });
}

void SuperDrunk::Brain()
{
}

void SuperDrunk::Hit(int amountDamage)
{
	if (lifes == 0)
		return;
	Enemy::Hit(amountDamage);
	if (!hasBeenHit) {
		hasBeenHit = true;
		internalTimer = 0;
	}
}

bool SuperDrunk::TryKill()
{
	return false;
}

void SuperDrunk::CheckCollisions()
{

	if (position.x - TILE_SIZE * 4 < 2 * TILE_SIZE) {
		direction.x = -direction.x;
		position.x = 2 * TILE_SIZE + TILE_SIZE * 4;
	}
	if (position.x + TILE_SIZE * 4 > (GAME_TILE_WIDTH - 2) * TILE_SIZE) {
		direction.x = -direction.x;
		position.x = (GAME_TILE_WIDTH - 2) * TILE_SIZE - TILE_SIZE * 4;
	}


	if (position.y > (GAME_TILE_HEIGHT - 1) * TILE_SIZE) {
		direction.y = -direction.y;
		position.y = (GAME_TILE_HEIGHT - 1) * TILE_SIZE;
	}
	if (position.y - TILE_SIZE * 8 < 3 * TILE_SIZE) {
		direction.y = -direction.y;
		position.y = 3 * TILE_SIZE + TILE_SIZE * 8;
	}

	Rectangle collision = GetCollider();
	for (size_t i = 0; i < EnemyManager::Instance().GetTargetsAmount(); i++)
	{
		Entity* x = EnemyManager::Instance().GetTarget(i);
		Player* player = dynamic_cast<Player*>(EnemyManager::Instance().GetTarget(i));
		if (player != nullptr && player->isActive) {

			if (CheckCollisionRecs(collision, player->GetCollision())) {
				if (lifes != 0 && (position.x != spawnPoint.x || position.y != spawnPoint.y)) {
					player->HitPlayer();
				}
				else {
					player->puntuationController->ModifyPuntutation(Kill());
				}
			}
		}
	}
}

Rectangle SuperDrunk::GetCollider()
{
	Rectangle collider = { position.x - TILE_SIZE * 4 * 0.7, position.y - TILE_SIZE * 9 * 0.8, TILE_SIZE * 8 * 0.7, TILE_SIZE * 8 * 0.8 };
	return collider;
}

void SuperDrunk::Reset()
{

}

bool SuperDrunk::MoveToSpawnPoint()
{
	bool arrived = true;

	Vector2 spawnPos = {spawnPoint.x ,spawnPoint.y };
	Vector2 moveDir = { (spawnPos.x - position.x) / abs(spawnPos.x - position.x),(spawnPos.y - position.y) / abs(spawnPos.y - position.y) };
	if (abs(spawnPos.x - position.x) > 0.2f) {
		position.x += moveDir.x * speed * deltaTime;
		arrived = false;
	}
	else {
		position.x = spawnPos.x;
	}
	if (abs(spawnPos.y - position.y) > 0.2f) {
		position.y += moveDir.y * speed  * deltaTime;
		arrived = false;
	}
	else {
		position.y = spawnPos.y;
	}

	direction.x = moveDir.x;

	return arrived;
}
