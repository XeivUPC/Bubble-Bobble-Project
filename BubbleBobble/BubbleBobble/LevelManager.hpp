#pragma once
#include <raylib.h>
#include "Level.hpp"
#include "SystemCalls.hpp"
#include "TileMapData.hpp"

class Level;
class TileMapData;
class LevelManager : public Entity
{
public:
	const int MAX_LEVELS = 8;
	LevelManager(SystemCalls* calls, TileMapData* tileMapData, Level* activeLevel, Level* waitingLevel);
	void LoadNewWaitingLevel(int loadedLevelIndex);
	void LoadNewActiveLevel(int loadedLevelIndex);
	void StartTransition();
	void EndTransition();

	void Update() override;
	void Render() override;

	int levelHeight = 30;
	int levelWidth = 32;

	int nextLevelIndex=2;

	Texture2D mapTileSet = LoadTexture("../Assets/Sprites/MapTileSet.png");
	TileMapData* _tileMapData;
	Level* _activeLevel;
	Level* _waitingLevel;
	
private:
	
	SystemCalls* _calls;
	bool isOnTransition = false;
	
};
