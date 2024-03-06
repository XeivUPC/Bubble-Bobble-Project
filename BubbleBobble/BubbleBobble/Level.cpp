#include "Level.hpp"
#include "../BubbleBobble/libraries/json.hpp"
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
	Collisions = new int[_levelManager->levelWidth * _levelManager->levelHeight];


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
				//DrawRectangle(x * _levelManager->_tileMapData->tileWidth + position.x,(y) *_levelManager->_tileMapData->tileHeight + position.y,_levelManager->_tileMapData->tileWidth,_levelManager->_tileMapData->tileHeight , BLUE);
			}
				
		}
	}
	
}

bool Level::IsTile(int x, int y, int* dataMap)
{
	if(dataMap[(int)y * _levelManager->levelWidth + (int)x] !=0)
		return true;
	return false;
}

int Level::GetTile(int x, int y, int* dataMap)
{
	return dataMap[(int)y * _levelManager->levelWidth + (int)x];

}
