#include "ElectricThunderBoltParticle.hpp"
#include "ElectricThunderBoltExplosionParticle.hpp"
#include "EnemyManager.hpp"

ElectricThunderBoltParticle::ElectricThunderBoltParticle(Vector2 position, Vector2 direction, Entity* owner)
{
	this->position = position;
	this->direction = direction;
	this->owner = owner;
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
	
	for (size_t i = 0; i < EnemyManager::Instance().enemies.size(); i++)
	{
		Enemy* enemy = EnemyManager::Instance().enemies[i];
		if (enemy->isActive && !enemy->IsInsideBubble())
		{
			if (CheckCollisionRecs(enemy->GetCollider(), { position.x - TILE_SIZE, position.y - TILE_SIZE,TILE_SIZE * 2,TILE_SIZE * 2 })) {
				
				Player* player = dynamic_cast<Player*>(owner);
				player->puntuationController->ModifyPuntutation(enemy->Kill());
				ParticleManager::Instance().AddParticle(new ElectricThunderBoltExplosionParticle(position));
				ParticleManager::Instance().RemoveParticle(this);
				break;
			}
		}
	}


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

	//DrawRectangle(position.x - TILE_SIZE, position.y - TILE_SIZE, TILE_SIZE * 2, TILE_SIZE * 2, {255,0,0,100});
}
