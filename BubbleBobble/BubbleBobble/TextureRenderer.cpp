#include "TextureRenderer.hpp"
#include <math.h>
#include <fstream>


TextureRenderer::~TextureRenderer() {

}

TextureRenderer::TextureRenderer()
{
}

TextureRenderer::TextureRenderer(Vector2 tileSize, Vector2 origin, Vector2 displacement) {
	this->tileSize = tileSize;
	this->origin = origin;
	this->displacement = displacement;
}

void TextureRenderer::Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation) {
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
void TextureRenderer::Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation, Color color)
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
void TextureRenderer::ChangeColor(Color color) {
	this->color = color;
}
void TextureRenderer::ChangeOrigin(Vector2 origin) {
	this->origin = origin;
}
void TextureRenderer::ChangeDisplacement(Vector2 displacement)
{
	this->displacement = displacement;
}
void TextureRenderer::ChangeTileSize(Vector2 tileSize) {
	this->tileSize = tileSize;
}
void TextureRenderer::FlipX() {
	flippedValueX *= -1;
}
void TextureRenderer::FlipY() {
	flippedValueY *= -1;
}
void TextureRenderer::FlipX(bool flip) {
	if (flip)
		flippedValueX = -1;
	else
		flippedValueX =1;
}
void TextureRenderer::FlipY(bool flip) {
	if (flip)
		flippedValueY = -1;
	else
		flippedValueY = 1;
}
bool TextureRenderer::IsFlippedX() {
	return flippedValueX < 0 ? true : false;
}
bool TextureRenderer::IsFlippedY() {
	return flippedValueY < 0 ? true : false;
}

int TextureRenderer::GetFlippedXValue()
{
	return flippedValueX;
}

int TextureRenderer::GetFlippedYValue()
{
	return flippedValueY;
}
