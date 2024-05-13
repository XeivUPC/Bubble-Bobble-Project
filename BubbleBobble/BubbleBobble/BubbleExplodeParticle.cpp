#include "BubbleExplodeParticle.hpp"

BubbleExplodeParticle::BubbleExplodeParticle(Vector2 position)
{
	this->position = position;
	Animation pop = { TextureManager::Instance().GetTexture("BasicParticlesTileset") ,0.1f };
	pop.frames.push_back({ 2 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	pop.frames.push_back({ 3 * TILE_REAL_SIZE * 2,2 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 2 });
	renderer.AddAnimation("PopBubbleParticle",pop);
	renderer.PlayAniamtion("PopBubbleParticle");
}

BubbleExplodeParticle::~BubbleExplodeParticle()
{
}

void BubbleExplodeParticle::Update()
{
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void BubbleExplodeParticle::Render()
{
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE, 0, WHITE);
}
