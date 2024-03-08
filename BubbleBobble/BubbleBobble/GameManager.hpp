#pragma once
#include <raylib.h>
#include "SystemCalls.hpp"
#include "PuntuationHolder.hpp"
#include "LevelManager.hpp"
#include "Level.hpp"
#include "Player.hpp"

class LevelManager;
class Level;
class Player;
class GameManager
{
public:
	//// Functions
	GameManager();
	void SaveGameData(int highScore);
	void LoadGameData(int* highScore);
	SystemCalls calls = SystemCalls();

	//// Points
	PuntuationHolder player1Points = PuntuationHolder(0, 1);
	PuntuationHolder player2Points = PuntuationHolder(0, 1);;
	PuntuationHolder highScore = PuntuationHolder(0, 1);;

	//// TileMap Data
	int TILE_HEIGHT = 30;
	int TILE_WIDTH = 30;

	int MAP_WIDTH = 32;
	int MAP_HEIGHT = 30;


	//// Levels
	LevelManager* levelManager = nullptr;
	Player* player = nullptr;

	Level* activeLevel;
	Level* waitingLevel;
private:
};

