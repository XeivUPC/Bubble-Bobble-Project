#include "ElectricThunderBoltParticle.hpp"

ElectricThunderBoltParticle::ElectricThunderBoltParticle(Vector2 position, Vector2 direction)
{
	this->position = position;
	this->direction = direction;

	Animation anim = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.2f };
	anim.frames.push_back({ 0 * TILE_REAL_SIZE * 2,5 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 1 * TILE_REAL_SIZE * 2,5 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 2 * TILE_REAL_SIZE * 2,5 * TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2, TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("ElectricThunderIdle", anim);
	renderer.PlayAniamtion("ElectricThunderIdle");
}

ElectricThunderBoltParticle::~ElectricThunderBoltParticle()
{
}

void ElectricThunderBoltParticle::Update()
{
	delayTimer += deltaTime;
	if (delayTimer<DELAY)
		return;

	/// <summary>
	/// / Check Collision -> Spawn Particle HIT
	/// </summary>

	position.x += direction.x * speed * deltaTime;
	position.y += direction.y * speed * deltaTime;
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void ElectricThunderBoltParticle::Render()
{
	if (delayTimer < DELAY)
		return;
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
}
