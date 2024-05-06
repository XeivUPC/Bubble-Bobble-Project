#pragma once
#include "Object.hpp"
#include "Fruit.hpp"
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

    void AddCollector(Entity* entity);
    Entity* GetCollectors(int index);
    int GetCollectorsAmount();

    std::vector<Object*> objects;

private:
	ObjectsManager();
	~ObjectsManager();

    std::vector<Entity*> collectors;
};



