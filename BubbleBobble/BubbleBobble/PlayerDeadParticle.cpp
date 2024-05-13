#include "PlayerDeadParticle.hpp"

PlayerDeadParticle::PlayerDeadParticle(Vector2 position)
{
	this->position = position;
	Animation pop = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.166f };
	pop.frames.push_back({ 0 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	pop.frames.push_back({ 1 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	pop.frames.push_back({ 2 * TILE_REAL_SIZE * 2,1 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("PopPlayerParticle", pop);
	renderer.PlayAniamtion("PopPlayerParticle");
}

PlayerDeadParticle::~PlayerDeadParticle()
{
}

void PlayerDeadParticle::Update()
{
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void PlayerDeadParticle::Render()
{
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE * 2, 0, WHITE);
}
