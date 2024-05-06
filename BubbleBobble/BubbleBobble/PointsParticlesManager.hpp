#pragma once
#include "Entity.hpp"
#include "PointParticle.hpp"
#define MAX_POINTS_PARTICLES_POOL  100
class PointsParticlesManager : public Entity
{
public:
    static PointsParticlesManager& Instance()
    {
        static PointsParticlesManager instance; //Guaranteed to be initialized only once
        return instance;
    }
    void Update() override;
    void Render() override;
    void Debug() override;
    void DisableAll();
    PointParticle* GetPointParticle();
private:
    //Private constructor to prevent instantiation
    PointsParticlesManager();
    //Destructor
    ~PointsParticlesManager();
    PointParticle* pointsParticlesPool = nullptr;
};

