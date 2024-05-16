#pragma once
#include "Particle.hpp"
class PointParticle : public Particle
{
#define LIFE_TIME 2
public:
    PointParticle(Vector2 position, int points);
    ~PointParticle();
    void Update() override;
    void Render() override;
private:
    int pointsValue;
    AnimationRenderer renderer;
    float speed = 8 * TILE_SIZE;
};

