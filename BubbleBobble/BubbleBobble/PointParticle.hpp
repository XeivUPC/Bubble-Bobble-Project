#pragma once
#include "Entity.hpp"
class PointParticle : public Entity
{
public:
    PointParticle();
    ~PointParticle();
    void Update() override;
    void Render() override;
    void Debug() override;
    void SetPointsValue(int value);
private:
    int pointsValue;
};

