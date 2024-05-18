#pragma once
#include "ParticleManager.hpp"

class ElectricThunderBoltExplosionParticle : public Particle
{
#define LIFE_TIME 0.6
public:
	ElectricThunderBoltExplosionParticle(Vector2 position);
	~ElectricThunderBoltExplosionParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
};

