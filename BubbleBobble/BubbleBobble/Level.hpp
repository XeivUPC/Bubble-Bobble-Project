#pragma once
#include <raylib.h>
#include "Entity.hpp"
#include "LevelManager.hpp"
#include "SpritePainter.hpp"
#include "TileMapData.hpp"

class LevelManager;
class TileMapData;
class SpritePainter;

class Level : public Entity
{
public:
	Level();
	Level(char* levelJsonPath, int levelNumber, LevelManager* levelManager);
	void Destroy() override;
	void Render() override;
	bool IsTile(int x, int y,int* dataMap);
	int GetTile(int x, int y,int* dataMap);
	int* Map;
	int* Collisions;
private:
	LevelManager* _levelManager;
	SpritePainter painter = SpritePainter(Vector2{ 8,8}, Vector2{0,0});
};
