#pragma once
#include <vector>
#include "Entity.hpp"
class SystemCalls : public Entity
{
public:
    SystemCalls();
    void Destroy() override;
    std::vector<Entity*> updateCall;
    std::vector<Entity*> destroyCall;
    std::vector<Entity*> lateUpdateCall;
    std::vector<Entity*> renderCall;
};