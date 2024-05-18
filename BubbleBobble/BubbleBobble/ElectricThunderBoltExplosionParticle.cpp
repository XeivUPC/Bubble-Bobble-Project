#include "ElectricThunderBoltExplosionParticle.hpp"


ElectricThunderBoltExplosionParticle::ElectricThunderBoltExplosionParticle(Vector2 position)
{
	this->position = position;

	Animation anim = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.1f };
	anim.frames.push_back({ 0 * TILE_REAL_SIZE * 2,6 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 1 * TILE_REAL_SIZE * 2,6 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 2 * TILE_REAL_SIZE * 2,6 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 0 * TILE_REAL_SIZE * 2,7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 1 * TILE_REAL_SIZE * 2,7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 2 * TILE_REAL_SIZE * 2,7 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("ElectricThunderIdle", anim);
	renderer.PlayAniamtion("ElectricThunderIdle");
}

ElectricThunderBoltExplosionParticle::~ElectricThunderBoltExplosionParticle()
{
}

void ElectricThunderBoltExplosionParticle::Update()
{
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void ElectricThunderBoltExplosionParticle::Render()
{
	
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);

	
}