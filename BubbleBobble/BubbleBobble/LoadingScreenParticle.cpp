#include "LoadingScreenParticle.hpp"

LoadingScreenParticle::LoadingScreenParticle(Vector2 position, Vector2 direction)
{
	this->position = position;
	this->direction = direction;

	Animation grow = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.2f };
	grow.frames.push_back({ 0 * TILE_REAL_SIZE * 2,3 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	grow.frames.push_back({ 1 * TILE_REAL_SIZE * 2,3 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	grow.frames.push_back({ 2 * TILE_REAL_SIZE * 2,3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	grow.frames.push_back({ 3 * TILE_REAL_SIZE * 2,3 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	grow.frames.push_back({ 0 * TILE_REAL_SIZE * 2,4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	grow.frames.push_back({ 1 * TILE_REAL_SIZE * 2,4 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("LoadingParticle", grow);
	renderer.PlayAniamtion("LoadingParticle");
}

LoadingScreenParticle::~LoadingScreenParticle()
{
}

void LoadingScreenParticle::Update()
{
	internalTimer += deltaTime;

	position.x += direction.x * speed * deltaTime;
	position.y += direction.y * speed * deltaTime;

	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void LoadingScreenParticle::Render()
{
	if (internalTimer < RENDER_DELAY)
		return;
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
}
