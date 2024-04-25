#include "EnemyManager.hpp"



void EnemyManager::Update()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
	}
}
void EnemyManager::Render()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render();
	}
}
void EnemyManager::RenderDebug()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->RenderDebug();
	}
}
void EnemyManager::SpawnZenChan(Vector2 tilePos, int direction)
{
	enemies.push_back(new ZenChan({ TILE_SIZE * tilePos.x,TILE_SIZE * tilePos.y }, direction));
}
void EnemyManager::SpawnMaita(Vector2 tilePos, int direction)
{
	enemies.push_back(new Maita({ TILE_SIZE * tilePos.x,TILE_SIZE * tilePos.y }, direction));
}
void EnemyManager::AddTarget(Entity* entity)
{
	targets.push_back(entity);
}
Entity* EnemyManager::GetTarget(int index)
{
	return targets[index];
}
int EnemyManager::GetTargetsAmount()
{
	return targets.size();
}
void EnemyManager::DestroyAll()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();
}
void EnemyManager::Reset()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Reset();
	}
}
EnemyManager::EnemyManager()
{
	
}

EnemyManager::~EnemyManager()
{
	DestroyAll();
}
