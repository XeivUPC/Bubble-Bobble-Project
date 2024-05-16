#include "LoadingScreenStaticParticle.hpp"

LoadingScreenStaticParticle::LoadingScreenStaticParticle(Vector2 position, float lifeTime)
{
	this->position = position;
	this->lifeTime = lifeTime;

	Animation anim = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.05f };
	anim.frames.push_back({ 3 * TILE_REAL_SIZE * 2,4 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	anim.frames.push_back({ 2* TILE_REAL_SIZE * 2,4 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });

	renderer.AddAnimation("LoadingParticleStatic", anim);
	renderer.PlayAniamtion("LoadingParticleStatic");
}

LoadingScreenStaticParticle::~LoadingScreenStaticParticle()
{
}

void LoadingScreenStaticParticle::Update()
{
	internalTimer += deltaTime;

	if (internalTimer > lifeTime) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void LoadingScreenStaticParticle::Render()
{
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
}
