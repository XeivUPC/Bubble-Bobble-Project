#include "Player.hpp"
#include <math.h>

Player::Player(SystemCalls* calls, TileMapData* tileMapData) {
	_calls = calls;
	_tileMapData = tileMapData;
	_calls->updateCall.push_back(this);
	_calls->renderCall.push_back(this);
	_calls->destroyCall.push_back(this);
	painter = SpritePainter(Vector2{ -16,16 }, Vector2{ (float)_tileMapData->tileWidth ,(float)_tileMapData->tileHeight*2 });
	position = { (float)_tileMapData->tileWidth*3 ,(float)_tileMapData->tileHeight *27};
}
void Player::Update() {
	direction = { 0,0 };
	if (IsKeyDown(KEY_D)) {
		direction.x+=3;
		painter.FlipX(true);
	}
	if (IsKeyDown(KEY_A)) {
		direction.x-=3;
		painter.FlipX(false);
	}
	if (IsKeyDown(KEY_W)) {
		direction.y-= 3;
	}
	if (IsKeyDown(KEY_S)) {
		direction.y+=3;
	}

	position.x += direction.x;
	position.y += direction.y;
}

void Player::Destroy() {

}
void Player::Render() {
	
	if (direction.x != 0) {
		xOffset += 0.2f;
		yOffset = 0;
		if (xOffset >= WALK_FRAMES)
			xOffset = 0;
	}
	else {
		xOffset += 0.07f;
		yOffset = 2;
		if (xOffset >= IDLE_FRAMES)
			xOffset = 0;
	}
	painter.Paint(playerTexture,position, Vector2{ (float)((int)xOffset) ,yOffset }, Vector2{(float)_tileMapData->tileWidth * 2, (float)(_tileMapData->tileHeight * 2) }, 0);
}