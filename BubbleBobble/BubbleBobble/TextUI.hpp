#pragma once
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "../Project1/libraries/json.hpp"
#include "Entity.hpp"
#include "SpritePainter.hpp"
#include "SystemCalls.hpp"
#include "TileMapData.hpp"

class TileMapData;

class TextUI :public Entity
{
public:
	TextUI(char*jsonPath,SystemCalls* calls, TileMapData* tileMapData, int width, int height, int xOffset, int yOffset);
	void Render() override;
	void Destroy() override;
	int* UI;
	
private:
	SpritePainter painter = SpritePainter((char*)"../Assets/Sprites/Text.png", Vector2{8,8}, Vector2{0,0});
	SystemCalls* _calls;
	TileMapData* _tileMapData;
	int _width;
	int _height;
	int _xOffset;
	int _yOffset;
};

