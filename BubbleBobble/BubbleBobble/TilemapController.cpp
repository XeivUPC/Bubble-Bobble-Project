#include "TilemapController.hpp"
#include "TilemapConfiguration.h"
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "json.hpp"

using namespace std;

TilemapController::TilemapController(Texture* texture,const char* path, int tilesXRow, Vector2 dimensions)
{
	this->texture = *texture;
	this->dimensions = dimensions;
	tilemap = new int[dimensions.x * dimensions.y];
	rowTiles = tilesXRow;
	LoadFromJson(path);
}

TilemapController::TilemapController(const char* path, int tilesXRow, Vector2 dimensions)
{
	this->dimensions = dimensions;
	tilemap = new int[dimensions.x * dimensions.y];
	rowTiles = tilesXRow;
	LoadFromJson(path);
}

TilemapController::~TilemapController()
{	
	delete[] tilemap;
	printf("TILEMAP DELETED CORRECTLY\n");
}

bool TilemapController::LoadFromJson(const char* path)
{
	try {
		if (path != nullptr)
		{
			ifstream fJson(path);
			stringstream buffer;
			buffer << fJson.rdbuf();
			auto json = nlohmann::json::parse(buffer.str());
			auto layers = json["layers"];
			auto tiles = layers[0]["data"];
			for (int index = 0; index < dimensions.x * dimensions.y; ++index)
			{
				tilemap[index] = tiles[index];
			}
			fJson.close();
		}
		else {
			for (int index = 0; index < dimensions.x * dimensions.y; ++index)
			{
				tilemap[index] = 0;
			}
		}
		return true;
	}
	catch (...) {
		printf("\n--------ERROR LOADING TILEMAP--------\n");
		return false;
	}
}

void TilemapController::ModifyTile(int index, int newValue)
{
	tilemap[index] = newValue;
}

void TilemapController::ModifyTile(int x, int y, int newValue)
{
	tilemap[(int)dimensions.x * y + x] = newValue;
}

void TilemapController::ModifyTile(Vector2 position, int newValue)
{
	tilemap[(int)(dimensions.x * position.y + position.x)] = newValue;
}

int TilemapController::GetTile(int index)
{
	return tilemap[index];
}

int TilemapController::GetTile(int x, int y)
{
	return tilemap[(int)dimensions.x * y + x];
}

int TilemapController::GetTile(Vector2 position)
{
	return tilemap[(int)(dimensions.x * position.y + position.x)];
}

Renderer& TilemapController::ModifyRenderer()
{
	return renderer;
}

void TilemapController::SetTexture(Texture* texture)
{
	this->texture = *texture;
}

Vector2 TilemapController::GetDimensions() {
	return Vector2{dimensions.x,dimensions.y};
}


void TilemapController::Render() {
	if (!isActive)
		return;
	for (float y = 0; y < dimensions.y; y++)
	{
		for (float x = 0; x < dimensions.x; x++)
		{
			float valueOfTile = GetTile((int)y * dimensions.x + (int)x);
			if (valueOfTile != 0) {
				float yOffset = floor((valueOfTile-1) / rowTiles);
				float xOffset = floor((valueOfTile) - yOffset * rowTiles);
				xOffset--;
				renderer.Paint(texture, Vector2{ (x)*TILE_SIZE,(y)*TILE_SIZE }, Vector2{ xOffset,yOffset }, {TILE_SIZE,TILE_SIZE}, 0);
			}

		}
	}
}