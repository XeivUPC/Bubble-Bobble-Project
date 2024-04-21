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

	bool IsTile(int x, int y, int* dataMap);
	int GetTile(int x, int y, int* dataMap);

	int* GetCollisionsTilemap();
	int* GetDirectionsTilemap();
	int* GetEnemiesTilemap();

private:
	int* Map = nullptr;
	int* Shadows = nullptr;
	int* Collisions = nullptr;
	int* Directions = nullptr;
	int* Enemies = nullptr;

	Color ShadowsColor=WHITE;

	void LoadJSON(string levelJsonPath);
};

