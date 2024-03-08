#pragma once
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "../BubbleBobble/libraries/json.hpp"
#include "VisualEntity.hpp"
#include "SystemCalls.hpp"


#include "GameManager.hpp"

class GameManager;

class TextUI : public VisualEntity
{
public:
	TextUI(char*jsonPath,GameManager* gameManager, int width, int height, int xOffset, int yOffset);
	void Destroy() override;
	void Render() override;
	int* UI;
	
private:
	GameManager* _gm;
	int _width;
	int _height;
	int _xOffset;
	int _yOffset;
};

