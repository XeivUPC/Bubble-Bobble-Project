#pragma once
#include "ParticleManager.hpp"

class ExplodeParticle : public Particle
{
#define LIFE_TIME 0.36
public:
	ExplodeParticle(Vector2 position, float delay);
	~ExplodeParticle();
	void Update() override;
	void Render() override;
private:
	float delay;
	float delayTimer = 0;
	AnimationRenderer renderer;
};

