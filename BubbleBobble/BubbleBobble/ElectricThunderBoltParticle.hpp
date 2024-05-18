#pragma once
#include "ParticleManager.hpp"

class ElectricThunderBoltParticle : public Particle
{
#define LIFE_TIME 2.5
#define DELAY 1
public:
	ElectricThunderBoltParticle(Vector2 position, Vector2 direction);
	~ElectricThunderBoltParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
	float speed = 32 * TILE_SIZE;
	float delayTimer = 0;
};

