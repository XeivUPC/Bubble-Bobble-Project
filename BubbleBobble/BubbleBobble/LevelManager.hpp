#pragma once
#include <raylib.h>
#include "Level.hpp"
#include "SystemCalls.hpp"
#include "TileMapData.hpp"
#include "Player.hpp"

#include "GameManager.hpp"
class GameManager;

class Level;
class TileMapData;
class Player;
class LevelManager : public Entity
{
public:
	
	LevelManager(GameManager* gameManager);
	void LoadNewWaitingLevel(int loadedLevelIndex);
	void LoadNewActiveLevel(int loadedLevelIndex);
	void StartTransition();
	void EndTransition();

	void Update() override;
	void Render() override;

	Texture2D mapTileSet = LoadTexture("../Assets/Sprites/MapTileSet.png");
	GameManager* _gm;
private:
	const int MAX_LEVELS = 8;
	int nextLevelIndex = 2;
	bool isOnTransition = false;
	
};
