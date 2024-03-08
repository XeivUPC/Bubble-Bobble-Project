#include "Level.hpp"
#include "../BubbleBobble/libraries/json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>


using namespace std;

Level::Level() {

}

Level::Level(char* levelJsonPath, int levelNumber, GameManager* gameManager)
{
	renderer = TextureRenderer(Vector2{ 8,8 }, Vector2{ 0,0 });
	_gm = gameManager;
	Map = new int[(_gm->MAP_WIDTH) * (_gm->MAP_HEIGHT)];
	Collisions = new int[(_gm->MAP_WIDTH) * (_gm->MAP_HEIGHT)];
	Directions = new int[(_gm->MAP_WIDTH) * (_gm->MAP_HEIGHT)];
	Enemies = new int[(_gm->MAP_WIDTH) * (_gm->MAP_HEIGHT)];


	if (levelJsonPath != nullptr) {
		ifstream fJson(levelJsonPath);

		stringstream buffer;
		buffer << fJson.rdbuf();
		auto json = nlohmann::json::parse(buffer.str());


		auto layers = json["layers"];
		auto tilesMap = layers[0]["data"];

		for (int index = 0; index < tilesMap.size(); ++index)
		{

			Map[index] = tilesMap[index];
		}

		auto tilesCollisions = layers[1]["data"];
		auto offset = json["tilesets"][1]["firstgid"];
		for (int index = 0; index < tilesCollisions.size(); ++index)
		{
			if (tilesCollisions[index]!=0) {
				Collisions[index] = tilesCollisions[index] - (int)offset + 1;
			}
			else {
				Collisions[index] = 0;
			}
			
		}
	}
	position = { 0,0 };

}

void Level::Render()
{
	for (float y = 0; y < _gm->MAP_HEIGHT; y++)
	{
		for (float x = 0; x < _gm->MAP_WIDTH; x++)
		{
			float valueOfTile = Map[(int)y * _gm->MAP_WIDTH + (int)x];
			if (valueOfTile != 0) {
				float yOffset = floor(valueOfTile / 32);
				float xOffset = floor(valueOfTile - yOffset *32);
				xOffset--;
				renderer.Paint(_gm->levelManager->mapTileSet, Vector2{ x * _gm->TILE_WIDTH + position.x,(y) *_gm->TILE_HEIGHT + position.y }, Vector2{ xOffset,yOffset }, Vector2{ (float)_gm->TILE_WIDTH,(float)_gm->TILE_HEIGHT }, 0);
				
				
			}
		}
	}
	
}
void Level::Destroy() {
	delete[] Map;
	delete[] Collisions;
	delete[] Directions;
	delete[] Enemies;
}

bool Level::IsTile(int x, int y, int* dataMap)
{
	if(dataMap[(int)y * _gm->MAP_WIDTH + (int)x] !=0)
		return true;
	return false;
}

int Level::GetTile(int x, int y, int* dataMap)
{
	return dataMap[(int)y * _gm->MAP_WIDTH + (int)x];

}
