#pragma once
#include <vector>
#include "Entity.hpp"
class SystemCalls : public Entity
{
public:
    SystemCalls();
    void Destroy() override;
    std::vector<Entity*> updateCall;
    std::vector<Entity*> lateUpdateCall;
    std::vector<Entity*> earlyUpdateCall;
    std::vector<Entity*> awakeCall;
    std::vector<Entity*> startCall;
    std::vector<Entity*> destroyCall;
    std::vector<Entity*> renderCall;
};