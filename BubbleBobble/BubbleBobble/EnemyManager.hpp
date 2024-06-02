#pragma once
#include "Enemy.hpp"
#include "ZenChan.hpp"
#include "Maita.hpp"
#include "SuperDrunk.hpp"
#include <vector>



#include "IRendereable.h"
#include "IUpdateable.h"
#include "IReseteable.h"
#include "IDebugeable.h"
class EnemyManager : public IRendereable, public IUpdateable, public IDebugeable, public IReseteable
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
    void Debug() override;
    void SpawnZenChan(Vector2 tilePos,int direction);
    void SpawnMaita(Vector2 tilePos, int direction);
    void SpawnSuperDrunk(Vector2 tilePos, int direction);
    void SpawnRandomEnemy(Vector2 tilePos, int direction);

    void AddTarget(Entity* entity);
    Entity* GetTarget(int index);
    void SetAngry(bool status);
    bool IsAngryMode();
    int GetTargetsAmount();
    void DestroyAll();
    void Reset() override;
    int EnemiesAlive();
    void KillAllEnemies();

    std::vector<Enemy*> enemies;

private:
    bool angryModeStatus = false;
	EnemyManager();
	~EnemyManager();

    std::vector<Entity*> targets;
};



