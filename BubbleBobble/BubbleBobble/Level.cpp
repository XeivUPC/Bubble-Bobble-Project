#include "Level.hpp"
#include "TilemapConfiguration.h"
#include "LevelManager.hpp"
#include "TextureManager.hpp"
#include "EnemyManager.hpp"
#include "ObjectsManager.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>


using namespace std;
Level::Level(string levelJsonPath, int levelNumber)
{
	Map = new int[(int)(GAME_TILE_WIDTH * GAME_TILE_HEIGHT)];
	Collisions = new int[(int)(GAME_TILE_WIDTH * GAME_TILE_HEIGHT)];
	Directions = new int[(int)(GAME_TILE_WIDTH * GAME_TILE_HEIGHT)];
	Shadows = new int[(int)(GAME_TILE_WIDTH * GAME_TILE_HEIGHT)];
	LoadJSON(levelJsonPath);
	position = { 0,0 };
	levelIndex = levelNumber+1;
}

Level::~Level()
{
	delete[] Map;
	delete[] Collisions;
	delete[] Directions;
	delete[] Shadows;
}

void Level::Render()
{
	for (int y = 0; y < GAME_TILE_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_TILE_WIDTH; x++)
		{
			float valueOfTile = GetTile(x, y, Map);
			if (valueOfTile != 0) {
				float yOffset = floor((valueOfTile-1) / 32);
				float xOffset = floor(valueOfTile - yOffset * 32);
				xOffset--;
				LevelManager& levelManager = LevelManager::Instance();
				TextureManager& textureManager = TextureManager::Instance();
				levelManager.GetRenderer()->Paint(*textureManager.GetTexture("MapTileSet"), Vector2{x * TILE_SIZE + position.x,(y)*TILE_SIZE + position.y}, Vector2{xOffset,yOffset}, Vector2{TILE_SIZE, TILE_SIZE}, 0);

				//Debug
				//DrawRectangle(x * dimensions.z + position.x, (y)*dimensions.w + position.y, dimensions.z, dimensions.w,BLUE);
				//DrawCircle(x * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE/2, 5, BLUE);
			}
			valueOfTile = GetTile(x, y, Shadows);
			if (valueOfTile != 0) {

				float yOffset = floor(valueOfTile / 8);
				float xOffset = floor(valueOfTile - yOffset * 8);
				xOffset--;
				LevelManager& levelManager = LevelManager::Instance();
				TextureManager& textureManager = TextureManager::Instance();
				levelManager.GetRenderer()->Paint(*textureManager.GetTexture("MapShadowsTileSet"), Vector2{x * TILE_SIZE + position.x,(y)*TILE_SIZE + position.y}, Vector2{xOffset,yOffset}, Vector2{TILE_SIZE, TILE_SIZE}, 0, ShadowsColor);

			}
		}
	}
}

void Level::Debug()
{
	for (int y = 0; y < GAME_TILE_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_TILE_WIDTH; x++)
		{
			float valueOfTile = GetTile(x, y, Map);
			if (valueOfTile != 0) {
				DrawRectangle(x * TILE_SIZE + position.x, (y)*TILE_SIZE + position.y, TILE_SIZE, TILE_SIZE, { 0,0,255,100 });				
			}
		}
	}
}

void Level::LoadEnemies()
{
	char delimiter = '\n';

	istringstream stream(enemiesData);
	string enemyData;
	int amountOfEnemies = std::count_if(enemiesData.begin(), enemiesData.end(), [](char c) {return c == '\n'; });

	while (amountOfEnemies > 0)
	{
		getline(stream, enemyData, delimiter);
		istringstream stream2(enemyData);
		string enemyName;
		string enemyPositions;
		char delimiter2 = '_';
		getline(stream2, enemyName, delimiter2);
		getline(stream2, enemyPositions, delimiter2);
		float xPos = stof(enemyPositions);
		getline(stream2, enemyPositions, delimiter2);
		float yPos = stof(enemyPositions);
		getline(stream2, enemyPositions, delimiter2);
		int enemyDir = stoi(enemyPositions);

		if (enemyName == "ZenChan") {
			EnemyManager::Instance().SpawnZenChan({ xPos,yPos, }, enemyDir);
		}
		if (enemyName == "Maita") {
			EnemyManager::Instance().SpawnMaita({ xPos,yPos }, enemyDir);
		}
		if (enemyName == "SuperDrunk") {
			EnemyManager::Instance().SpawnSuperDrunk({xPos,yPos},enemyDir);
		}
		amountOfEnemies--;
	}
}

void Level::LoadItems()
{
	char delimiter = '\n';

	istringstream stream(itemsData);
	string itemData;
	int amountOfItems= std::count_if(itemsData.begin(), itemsData.end(), [](char c) {return c == '\n'; });

	while (amountOfItems > 0)
	{
		getline(stream, itemData, delimiter);
		istringstream stream2(itemData);
		
		string itemPositions;
		char delimiter2 = '_';


		string itemType;
		getline(stream2, itemType, delimiter2);

		string itemData;
		getline(stream2, itemData, delimiter2);
		float xOffset = stof(itemData);
		getline(stream2, itemData, delimiter2);
		float yOffset = stof(itemData);
		getline(stream2, itemData, delimiter2);
		float xPos = stof(itemData);
		getline(stream2, itemData, delimiter2);
		float yPos = stof(itemData);
		getline(stream2, itemData, delimiter2);
		float points = stof(itemData);

		if (itemType == "Fruit") {
			ObjectsManager::Instance().SpawnFruit({ xOffset ,yOffset }, { xPos,yPos, }, points);
		}
		if (itemType == "PowerUp") {
			getline(stream2, itemData, delimiter2);
			float powerUpIndex = stof(itemData);
			ObjectsManager::Instance().SpawnPowerUp({ xOffset ,yOffset }, { xPos,yPos, }, points, powerUpIndex);
		}
		amountOfItems--;
	}
}

string Level::GetEnemiesData()
{
	return enemiesData;
}

string Level::GetItemsData()
{
	return itemsData;
}

bool Level::IsTile(int x, int y, int* dataMap)
{
	if (x < 0 || x >= GAME_TILE_WIDTH || y < 0 || y >= GAME_TILE_HEIGHT)
		return false;
	if (dataMap[y * (int)GAME_TILE_WIDTH + x] != 0)
		return true;
	return false;
}

int Level::GetTile(int x, int y, int* dataMap)
{
	return dataMap[y * (int)GAME_TILE_WIDTH + x];
}

int* Level::GetCollisionsTilemap()
{
	return Collisions;
}

int* Level::GetDirectionsTilemap()
{
	return Directions;
}

int Level::GetLevelIndex()
{
	return levelIndex;
}

void Level::LoadJSON(string levelJsonPath)
{
	try {
		ifstream fJson(levelJsonPath);

		stringstream buffer;
		buffer << fJson.rdbuf();

		buffer.clear();
		buffer.seekg(0);

		auto json = nlohmann::json::parse(buffer.str());

		auto layers = json["layers"];
		auto tilesMap = layers[0]["data"];


		for (int index = 0; index < GAME_TILE_WIDTH * GAME_TILE_HEIGHT; ++index)
		{
			Map[index] = tilesMap[index];

		}

		////Enemies
		enemiesData = layers[0]["properties"][0]["value"];
		itemsData = layers[0]["properties"][1]["value"];
		




		auto tilesCollisions = layers[1]["data"];
		auto offsetCollisions = json["tilesets"][1]["firstgid"];
		for (int index = 0; index < GAME_TILE_WIDTH * GAME_TILE_HEIGHT; ++index)
		{
			if (tilesCollisions[index] != 0) {
				Collisions[index] = tilesCollisions[index] - (int)offsetCollisions + 1;
			}
			else {
				Collisions[index] = 0;
			}

		}

		auto tilesDirections = layers[2]["data"];
		auto offsetDirections = json["tilesets"][2]["firstgid"];
		for (int index = 0; index < GAME_TILE_WIDTH * GAME_TILE_HEIGHT; ++index)
		{
			if (tilesDirections[index] != 0) {
				Directions[index] = tilesDirections[index] - (int)offsetDirections + 1;
			}
			else {
				Directions[index] = 0;
			}
		}

		auto tilesShadows = layers[3]["data"];
		auto offsetShadows = json["tilesets"][3]["firstgid"];
		auto color = layers[3]["properties"][0]["value"];
		string hexString = (string)color;
		hexString.erase(hexString.begin());
		hexString.erase(hexString.begin());
		hexString.erase(hexString.begin());
		unsigned int hexCode = stoi(hexString, 0, 16);

		ShadowsColor = GetColor(hexCode);
		ShadowsColor = { ShadowsColor.g,ShadowsColor.b,ShadowsColor.a,255 };
		for (int index = 0; index < GAME_TILE_WIDTH * GAME_TILE_HEIGHT; ++index)
		{
			if (tilesShadows[index] != 0) {
				Shadows[index] = tilesShadows[index] - (int)offsetShadows + 1;
			}
			else {
				Shadows[index] = 0;
			}
		}




		fJson.close();
	}
	catch (...) {
		printf("\n--------ERROR LOADING TILEMAP--------\n");
	}
}
