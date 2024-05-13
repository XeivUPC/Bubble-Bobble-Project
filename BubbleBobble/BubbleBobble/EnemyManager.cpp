#include "EnemyManager.hpp"



void EnemyManager::Update()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isActive)
			enemies[i]->Update();
	}
}
void EnemyManager::Render()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isActive)
			enemies[i]->Render();
	}
}
void EnemyManager::Debug()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isActive)
			enemies[i]->Debug();
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
void EnemyManager::SetAngry(bool status)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->isAngry=status;
	}
	angryModeStatus = status;
}
bool EnemyManager::IsAngryMode()
{
	return angryModeStatus;
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
int EnemyManager::EnemiesAlive()
{
	int amount = 0;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isActive)
			amount++;
	}
	return amount;
}
void EnemyManager::KillAllEnemies()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->isActive = false;
	}
}
EnemyManager::EnemyManager()
{
	
}

EnemyManager::~EnemyManager()
{
	DestroyAll();
}
