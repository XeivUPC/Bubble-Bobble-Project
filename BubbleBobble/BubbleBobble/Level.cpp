#include "Level.hpp"
#include "TilemapConfiguration.h"
#include "LevelManager.hpp"
#include "TextureManager.hpp"
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
	Enemies = new int[(int)(GAME_TILE_WIDTH * GAME_TILE_HEIGHT)];
	Shadows = new int[(int)(GAME_TILE_WIDTH * GAME_TILE_HEIGHT)];
	LoadJSON(levelJsonPath);
	position = { 0,0 };
}

Level::~Level()
{
	delete[] Map;
	delete[] Collisions;
	delete[] Directions;
	delete[] Enemies;
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
				float yOffset = floor(valueOfTile / 32);
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

bool Level::IsTile(int x, int y, int* dataMap)
{
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

int* Level::GetEnemiesTilemap()
{
	return Enemies;
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
