#pragma once
#include "Entity.hpp"
class PointParticle : public Entity
{
public:
    PointParticle();
    ~PointParticle();
    void Update() override;
    void Render() override;
    void RenderDebug() override;
    void SetPointsValue(int value);
private:
    int pointsValue;
};

