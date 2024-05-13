#pragma once
#include "ParticleManager.hpp"

class BubbleExplodeParticle : public Particle
{
#define LIFE_TIME 1
public: 
	BubbleExplodeParticle(Vector2 position);
	~BubbleExplodeParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
};

