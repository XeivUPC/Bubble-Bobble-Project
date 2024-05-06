#include "Renderer.hpp"
#include <math.h>
#include <fstream>


Renderer::~Renderer() {

}

Renderer::Renderer()
{
}

Renderer::Renderer(Vector2 tileSize, Vector2 origin, Vector2 displacement) {
	this->tileSize = tileSize;
	this->origin = origin;
	this->displacement = displacement;
}

void Renderer::Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation) {
	////TODO--> Update Texture By Time
	sourceRec = {
	    textureOffset.x* (int)tileSize.x* flippedValueX, // X position of the top-left corner of the tile in the spritesheet
		textureOffset.y* (int)tileSize.y* flippedValueY,  // Y position of the top-left corner of the tile in the spritesheet
		tileSize.x, // Width of the tile
		tileSize.y // Height of the tile
	};
	destRec = {
		position.x + displacement.x, // X position on the screen (change this as needed)
		position.y + displacement.y, // Y position on the screen (centered vertically)
		screenSize.x,             // Width of the tile on the screen
		screenSize.y              // Height of the tile on the screen
	};
	DrawTexturePro(texture, sourceRec, destRec, origin, rotation, color);
}
void Renderer::Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation, Color color)
{
	////TODO--> Update Texture By Time
	sourceRec = {
	    textureOffset.x * (int)tileSize.x * flippedValueX, // X position of the top-left corner of the tile in the spritesheet
		textureOffset.y * (int)tileSize.y * flippedValueY,  // Y position of the top-left corner of the tile in the spritesheet
		tileSize.x, // Width of the tile
		tileSize.y // Height of the tile
	};
	destRec = {
		position.x + displacement.x, // X position on the screen (change this as needed)
		position.y + displacement.y, // Y position on the screen (centered vertically)
		screenSize.x,             // Width of the tile on the screen
		screenSize.y              // Height of the tile on the screen
	};
	DrawTexturePro(texture, sourceRec, destRec, origin, rotation, color);
}
void Renderer::ChangeColor(Color color) {
	this->color = color;
}
void Renderer::ChangeOrigin(Vector2 origin) {
	this->origin = origin;
}
void Renderer::ChangeDisplacement(Vector2 displacement)
{
	this->displacement = displacement;
}
void Renderer::ChangeTileSize(Vector2 tileSize) {
	this->tileSize = tileSize;
}
void Renderer::FlipX() {
	flippedValueX *= -1;
}
void Renderer::FlipY() {
	flippedValueY *= -1;
}
void Renderer::FlipX(bool flip) {
	if (flip)
		flippedValueX = -1;
	else
		flippedValueX =1;
}
void Renderer::FlipY(bool flip) {
	if (flip)
		flippedValueY = -1;
	else
		flippedValueY = 1;
}
bool Renderer::IsFlippedX() {
	return flippedValueX < 0 ? true : false;
}
bool Renderer::IsFlippedY() {
	return flippedValueY < 0 ? true : false;
}

int Renderer::GetFlippedXValue()
{
	return flippedValueX;
}

int Renderer::GetFlippedYValue()
{
	return flippedValueY;
}
