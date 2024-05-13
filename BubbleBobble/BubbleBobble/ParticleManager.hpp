#pragma once
#include <vector>
#include "Particle.hpp"

#include "IRendereable.h"
#include "IUpdateable.h"
#include "IReseteable.h"
#include "IDebugeable.h"
class ParticleManager : public IRendereable, public IUpdateable, public IDebugeable
{
public:
    static ParticleManager& Instance()
    {
        static ParticleManager instance; //Guaranteed to be initialized only once
        return instance;
    }

    void Update() override;
    void Render() override;
    void Debug() override;

    void AddParticle (Particle* newParticle);
    void RemoveParticle (Particle* particleToRemove);
    void DestroyAll();
private:
    ParticleManager();
    ~ParticleManager();
    std::vector<Particle*> particles;
};



