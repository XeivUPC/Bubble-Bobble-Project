#include "ExplodeParticle.hpp"

ExplodeParticle::ExplodeParticle(Vector2 position, float delay)
{
	this->position = position;
	this->delay = delay;
	Animation explode = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.12f };
	explode.frames.push_back({ 3 * TILE_REAL_SIZE * 2,5 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	explode.frames.push_back({ 3 * TILE_REAL_SIZE * 2,6 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	explode.frames.push_back({ 3 * TILE_REAL_SIZE * 2,7 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("EplodeParticle", explode);
	renderer.PlayAniamtion("EplodeParticle");
}

ExplodeParticle::~ExplodeParticle()
{
}

void ExplodeParticle::Update()
{
	delayTimer += deltaTime;
	if (delayTimer < delay)
		return;
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void ExplodeParticle::Render()
{
	if (delayTimer < delay)
		return;
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
	
	
}
