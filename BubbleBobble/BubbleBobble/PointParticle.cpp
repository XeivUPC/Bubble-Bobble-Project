#include "PointParticle.hpp"

PointParticle::PointParticle(Vector2 position, int points)
{

	Animation anim = { TextureManager::Instance().GetTexture("PointsParticlesTileSet"),4 };
	anim.frames.push_back({ 0 * TILE_REAL_SIZE * 3,0 * TILE_REAL_SIZE * 3,TILE_REAL_SIZE * 3,TILE_REAL_SIZE * 3 });
	renderer.AddAnimation("PointParticleBasic", anim);
	renderer.PlayAniamtion("PointParticleBasic");
}

PointParticle::~PointParticle()
{

}

void PointParticle::Update()
{

}

void PointParticle::Render()
{

}