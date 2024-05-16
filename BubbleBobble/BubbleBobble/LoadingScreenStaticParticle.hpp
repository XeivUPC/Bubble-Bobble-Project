#pragma once
#include "ParticleManager.hpp"

class LoadingScreenStaticParticle : public Particle
{
public:
	LoadingScreenStaticParticle(Vector2 position, float lifeTime);
	~LoadingScreenStaticParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
	float lifeTime;
};

