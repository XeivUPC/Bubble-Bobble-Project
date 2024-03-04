#include "Level.hpp"
#include "../Project1/libraries/json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>


using namespace std;

Level::Level() {

}
Level::Level(char* levelJsonPath, int levelNumber, LevelManager* levelManager)
{
	_levelManager = levelManager;
	Map = new int[_levelManager->levelWidth * _levelManager->levelHeight];


	if (levelJsonPath != nullptr) {
		ifstream fJson(levelJsonPath);

		stringstream buffer;
		buffer << fJson.rdbuf();
		auto json = nlohmann::json::parse(buffer.str());


		auto tiles = json["data"];

		for (int index = 0; index < tiles.size(); ++index)
		{

			Map[index] = tiles[index];
		}
	}
	position = { 0,0 };

}
void Level::Destroy() {
	delete[] Map;
}
void Level::Render()
{
	for (float y = 0; y < _levelManager->levelHeight; y++)
	{
		for (float x = 0; x < _levelManager->levelWidth; x++)
		{
			float valueOfTile = Map[(int)y * _levelManager->levelWidth + (int)x];
			if (valueOfTile != 0) {
				float yOffset = floor(valueOfTile / 20);
				float xOffset = floor(valueOfTile - yOffset *20);
				xOffset--;
				painter.Paint(_levelManager->mapTileSet, Vector2{ x * _levelManager->_tileMapData->tileWidth + position.x,(y) *_levelManager->_tileMapData->tileHeight + position.y }, Vector2{ xOffset,yOffset }, Vector2{ (float)_levelManager->_tileMapData->tileWidth,(float)_levelManager->_tileMapData->tileHeight }, 0);
			}
				
		}
	}
	
}
