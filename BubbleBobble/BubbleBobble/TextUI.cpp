#include "TextUI.hpp"


using namespace std;
TextUI::TextUI(char* jsonPath,SystemCalls* calls, TileMapData* tileMapData, int width, int height, int xOffset, int yOffset)
{
	_calls = calls;
	_calls->renderCall.push_back(this);
	_calls->destroyCall.push_back(this);
	_tileMapData = tileMapData;
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
			float valueOfTile = UI[(int)y*_tileMapData->tileMapWidth + (int)x];
			if (valueOfTile != 0) {
				float yOffset = floor(valueOfTile / 61);
				float xOffset = floor(valueOfTile - yOffset * 61);
				xOffset--;
				painter.Paint(Vector2{ (x + _xOffset)* _tileMapData->tileWidth,(y+_yOffset) * _tileMapData->tileHeight }, Vector2{ xOffset,yOffset }, Vector2{ (float)_tileMapData->tileWidth,(float)_tileMapData->tileHeight }, 0);
			}

		}
	}
}

void TextUI::Destroy() {
	delete[] UI;
}
