#pragma once
#include "ParticleManager.hpp"
class PlayerConfuseParticle : public Particle
{
#define LIFE_TIME 1
public:
	PlayerConfuseParticle(Vector2 position);
	~PlayerConfuseParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
};


