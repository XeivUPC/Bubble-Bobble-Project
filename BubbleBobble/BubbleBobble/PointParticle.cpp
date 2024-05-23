#include "PointParticle.hpp"

PointParticle::PointParticle(Vector2 position, int points)
{
	this->position = position;
	direction = { 0,-1 };
	

	for (size_t i = 0; i < 38; i++)
	{
		if (pointsIndex[i] == points)
		{
			renderPos.y = (i / 9);
			renderPos.x = i - 9 * renderPos.y;
			break;
		}
	}

	Animation anim = { TextureManager::Instance().GetTexture("PointsParticlesTileSet"),4 };
	anim.frames.push_back({ renderPos.x * TILE_REAL_SIZE * 3,renderPos.y * TILE_REAL_SIZE * 3,TILE_REAL_SIZE * 3,TILE_REAL_SIZE * 3 });
	renderer.AddAnimation("PointParticleBasic", anim);
	renderer.PlayAniamtion("PointParticleBasic");
}

PointParticle::~PointParticle()
{

}

void PointParticle::Update()
{
	position.y += direction.y * speed * deltaTime;
	internalTimer += deltaTime;
	if (internalTimer > LIFE_TIME) {
		ParticleManager::Instance().RemoveParticle(this);
	}
}

void PointParticle::Render()
{
	renderer.UpdateAnimation();
	renderer.Draw(position.x - TILE_SIZE, position.y - TILE_SIZE * 2, 0, WHITE);
}

