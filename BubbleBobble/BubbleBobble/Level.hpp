#pragma once
#include <raylib.h>
#include "Entity.hpp"
#include <string>

using namespace std;
class Level : public Entity
{
public:
	Level(string levelJsonPath, int levelNumber);
	~Level();

	void Render() override;
	void Debug() override;
	void LoadEnemies();
	void LoadItems();
	string GetEnemiesData();
	string GetItemsData();

	bool IsTile(int x, int y, int* dataMap);
	int GetTile(int x, int y, int* dataMap);

	int* GetCollisionsTilemap();
	int* GetDirectionsTilemap();
	int GetLevelIndex();
private:
	int* Map = nullptr;
	int* Shadows = nullptr;
	int* Collisions = nullptr;
	int* Directions = nullptr;

	int levelIndex = 0;
	string enemiesData;
	string itemsData;
	Color ShadowsColor=WHITE;

	void LoadJSON(string levelJsonPath);
};

