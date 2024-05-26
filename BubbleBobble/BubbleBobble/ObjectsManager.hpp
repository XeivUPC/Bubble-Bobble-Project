#pragma once
#include "Object.hpp"
#include "FruitObject.hpp"
#include "PowerUpObject.hpp"
#include <vector>


#include "IRendereable.h"
#include "IUpdateable.h"
#include "IReseteable.h"
#include "IDebugeable.h"

class ObjectsManager : public IRendereable, public IUpdateable, public IDebugeable, public IReseteable
{
public:
    static ObjectsManager& Instance()
    {
        static ObjectsManager instance; //Guaranteed to be initialized only once
        return instance;
    }
    void Update() override;
    void Render() override;
    void Debug() override;
    void Reset() override;
    void RemoveObject(Object* object);
    void DestroyAll();
    void SpawnPowerUp(Vector2 textureOffset, Vector2 position, float points, float powerUpIndex);
    void SpawnFruit(Vector2 textureOffset, Vector2 position, float points);

    void AddCollector(Entity* entity);
    Entity* GetCollectors(int index);
    int GetCollectorsAmount();

    std::vector<Object*> objects;

private:
	ObjectsManager();
	~ObjectsManager();

    std::vector<Entity*> collectors;
};



