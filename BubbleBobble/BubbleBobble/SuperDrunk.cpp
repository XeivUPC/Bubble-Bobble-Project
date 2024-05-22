#include "SuperDrunk.hpp"
#include "EnemyManager.hpp"

SuperDrunk::SuperDrunk(Vector2 tilePos, int lookAt) {
	position = tilePos;
	direction = {1,1};
	speed = TILE_SIZE * 6.f;

	TextureManager::Instance().CreateTexture("Assets/Sprites/Boss.png", "SuperDrunkSpriteSheet");

	Animation normalAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	normalAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	normalAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	normalAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	normalAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 8, 0 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

	Animation angryAnim = { TextureManager::Instance().GetTexture("SuperDrunkSpriteSheet") ,0.12f };
	angryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8, 1 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });
	angryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8, 1 * TILE_REAL_SIZE * 8, -TILE_REAL_SIZE * 8, TILE_REAL_SIZE * 8 });

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
	renderer.AddAnimation("SuperDrunkBubble", bubbleAnim);

	renderer.PlayAniamtion("SuperDrunkNormal");
}

SuperDrunk::~SuperDrunk()
{

}

void SuperDrunk::Update()
{

	CheckCollisions();

	position.x += direction.x * speed * deltaTime;
	position.y += direction.y * speed * deltaTime;

}

void SuperDrunk::Render()
{
	if (direction.x > 0) {
		renderer.FlipX(false);
	}
	else {
		renderer.FlipX(true);
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

void SuperDrunk::CheckCollisions()
{

	if (position.x - TILE_SIZE * 4 < 2 * TILE_SIZE) {
		direction.x = -direction.x;
	}
	if (position.x + TILE_SIZE * 4 > (GAME_TILE_WIDTH - 2) * TILE_SIZE) {
		direction.x = -direction.x;
	}


	if (position.y > (GAME_TILE_HEIGHT - 1) * TILE_SIZE) {
		direction.y = -direction.y;
	}
	if (position.y - TILE_SIZE * 8 < 3 * TILE_SIZE) {
		direction.y = -direction.y;
	}

	Rectangle collision = GetCollider();
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

Rectangle SuperDrunk::GetCollider()
{
	Rectangle collider = { position.x - TILE_SIZE * 4 * 0.7, position.y - TILE_SIZE * 8 * 0.8, TILE_SIZE * 8 * 0.7, TILE_SIZE * 8 * 0.8 };
	return collider;
}

void SuperDrunk::Reset()
{

}
