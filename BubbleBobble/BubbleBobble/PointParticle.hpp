#pragma once
#include "ParticleManager.hpp"
class PointParticle : public Particle
{
#define LIFE_TIME 2
public:
    PointParticle(Vector2 position, int points);
    ~PointParticle();
    void Update() override;
    void Render() override;
private:
    AnimationRenderer renderer;
    float speed = 3 * TILE_SIZE;

    Vector2 renderPos{ 0,0 };
    int pointsIndex[38] = {
        10,20,30,40,50,60,70,80,90,100, 150, 200, 250, 300, 350, 400, 450, 500,
        550, 600, 650, 700, 750, 800, 850, 900, 950,
        1000, 1200, 2000, 3000, 4000, 5000, 6000, 7000, 8000,9000,10000
    };
};

