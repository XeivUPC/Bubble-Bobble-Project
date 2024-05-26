#include "ObjectsManager.hpp"


ObjectsManager::ObjectsManager()
{
	//objects.push_back(new FruitObject({6,1}, {10*TILE_SIZE,12 * TILE_SIZE },100));
	//objects.push_back(new PowerUpObject({8,7}, {25*TILE_SIZE,12 * TILE_SIZE },1000,1));
}

ObjectsManager::~ObjectsManager()
{
	DestroyAll();
}

void ObjectsManager::Update()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}
}

void ObjectsManager::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}

void ObjectsManager::Debug()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Debug();
	}
}

void ObjectsManager::Reset()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Reset();
	}
}

void ObjectsManager::RemoveObject(Object* object)
{
	int index =-1;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i] == object)
			index = i;
	}
	if (index == -1)
		return;
	objects.erase(objects.begin() + index);
	delete object;
}

void ObjectsManager::DestroyAll() {
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();
}

void ObjectsManager::SpawnPowerUp(Vector2 textureOffset, Vector2 position, float points, float powerUpIndex)
{
	objects.push_back(new PowerUpObject(textureOffset, { TILE_SIZE * position.x,TILE_SIZE * position.y }, points, powerUpIndex));
}

void ObjectsManager::SpawnFruit(Vector2 textureOffset, Vector2 position, float points)
{
	objects.push_back(new FruitObject(textureOffset, { TILE_SIZE * position.x,TILE_SIZE * position.y }, points));
}

void ObjectsManager::AddCollector(Entity* entity)
{
	collectors.push_back(entity);
}

Entity* ObjectsManager::GetCollectors(int index)
{
	return collectors[index];
}

int ObjectsManager::GetCollectorsAmount()
{
	return collectors.size();
}
