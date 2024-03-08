#pragma once
#include <raylib.h>
#include "VisualEntity.hpp"
#include "GameManager.hpp"

class GameManager;

class Level : public VisualEntity
{
public:
	Level();
	Level(char* levelJsonPath, int levelNumber, GameManager* levelManager);
	void Render() override;
	void Destroy() override;
	bool IsTile(int x, int y,int* dataMap);
	int GetTile(int x, int y,int* dataMap);
	int* Map;
	int* Collisions;
	int* Directions;
	int* Enemies;
private:
	GameManager* _gm;
};
