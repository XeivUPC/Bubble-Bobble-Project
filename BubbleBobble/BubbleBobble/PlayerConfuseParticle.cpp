#include "PlayerConfuseParticle.hpp"
PlayerConfuseParticle::PlayerConfuseParticle(Vector2 position)
{
	this->position = position;
	Animation confuse = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.0625f };
	confuse.frames.push_back({ 0 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	confuse.frames.push_back({ 1 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	confuse.frames.push_back({ 2 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	confuse.frames.push_back({ 3 * TILE_REAL_SIZE * 2,0 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("ConfuseParticle", confuse);
	renderer.PlayAniamtion("ConfuseParticle");
}

PlayerConfuseParticle::~PlayerConfuseParticle()
{
}

void PlayerConfuseParticle::Update()
{
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void PlayerConfuseParticle::Render()
{
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE * 2, 0, WHITE);
}
