#include "TextUI.hpp"


using namespace std;
TextUI::TextUI(char* jsonPath, GameManager* gameManager, int width, int height, int xOffset, int yOffset)
{
	renderer = TextureRenderer((char*)"../Assets/Sprites/Text.png", Vector2{ 8,8 }, Vector2{ 0,0 });
	_gm = gameManager;
	_gm->calls.renderCall.push_back(this);
	_width = width;
	_height = height;
	_xOffset = xOffset;
	_yOffset = yOffset;

	UI = new int[_width * _height];

	if(jsonPath!= nullptr)
	{
		ifstream fJson(jsonPath);

		stringstream buffer;
		buffer << fJson.rdbuf();
		auto json = nlohmann::json::parse(buffer.str());

		auto tiles = json["data"];
		for (int index = 0; index < tiles.size(); ++index)
		{
			UI[index] = tiles[index];
		}
	}
	else {
		for (int index = 0; index < _width*_height; ++index)
		{

			UI[index] = 0;
		}
	}	
}

void TextUI::Render()
{
	for (float y = 0; y < _height; y++)
	{
		for (float x = 0; x < _width; x++)
		{
			float valueOfTile = UI[(int)y*_gm->MAP_WIDTH + (int)x];
			if (valueOfTile != 0) {
				float yOffset = floor(valueOfTile / 64);
				float xOffset = floor(valueOfTile - yOffset * 64);
				xOffset--;
				renderer.Paint(Vector2{ (x + _xOffset)* _gm->TILE_WIDTH,(y+_yOffset) * _gm->TILE_HEIGHT }, Vector2{ xOffset,yOffset }, Vector2{ (float)_gm->TILE_WIDTH,(float)_gm->TILE_HEIGHT }, 0);
			}

		}
	}
}

void TextUI::Destroy() {
	delete[] UI;
}
