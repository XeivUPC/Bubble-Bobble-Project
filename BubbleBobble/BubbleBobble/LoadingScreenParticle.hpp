#pragma once
#include "ParticleManager.hpp"

class LoadingScreenParticle : public Particle
{
#define LIFE_TIME 1
#define RENDER_DELAY 0.03
public:
	LoadingScreenParticle(Vector2 position, Vector2 direction);
	~LoadingScreenParticle();
	void Update() override;
	void Render() override;
private:
	AnimationRenderer renderer;
	float speed = 16*TILE_SIZE;
}; 


