#pragma once
#include "Enemy.hpp"
#include "ZenChan.hpp"
#include "Maita.hpp"
#include <vector>
class EnemyManager : public Entity
{
    friend class Enemy;
public:
    static EnemyManager& Instance()
    {
        static EnemyManager instance; //Guaranteed to be initialized only once
        return instance;
    }

    void Update() override;
    void Render() override;
    void RenderDebug() override;
    void AddTarget(Entity* entity);
    Entity* GetTarget(int index);
    int GetTargetsAmount();
    void Reset() override;

    std::vector<Enemy*> enemies;

private:
	EnemyManager();
	~EnemyManager();

    std::vector<Entity*> targets;
};



