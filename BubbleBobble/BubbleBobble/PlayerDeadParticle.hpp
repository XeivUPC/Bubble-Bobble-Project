#pragma once
#include "ParticleManager.hpp"
class PlayerDeadParticle : public Particle
{
#define LIFE_TIME 0.5
public:
	PlayerDeadParticle(Vector2 position);
	~PlayerDeadParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
};
