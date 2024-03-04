#pragma once
#include <raylib.h>
#include "Entity.hpp"
#include "SpritePainter.hpp"
#include "SystemCalls.hpp"
#include "TileMapData.hpp"

class TileMapData;

class Player : public Entity
{
public:
	Player(SystemCalls* calls, TileMapData* tileMapData);
	void Destroy() override;
	void Update() override;
	void Render() override;
private:
	Texture2D playerTexture = LoadTexture("../Assets/Sprites/Player.png");
	SystemCalls* _calls;
	TileMapData* _tileMapData;
	SpritePainter painter;

	float xOffset=0;
	float yOffset=0;
	Vector2 direction;

	/////AnimationConstants
	const int WALK_FRAMES=5;
	const int IDLE_FRAMES=2;
};