#include "TextureRenderer.hpp"
#include <math.h>

TextureRenderer::TextureRenderer() {

}
TextureRenderer::TextureRenderer(char* filePath, Vector2 tileSize, Vector2 origin) {
	texture = LoadTexture(filePath);
	this->tileSize = tileSize;
	this->origin = origin;
}
TextureRenderer::TextureRenderer(Vector2 tileSize, Vector2 origin) {
	this->tileSize = tileSize;
	this->origin = origin;
}
void TextureRenderer::Paint(Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation) {
	////TODO--> Update Texture By Time
	sourceRec = {
		textureOffset.x * abs((int)tileSize.x), // X position of the top-left corner of the tile in the spritesheet
		textureOffset.y * abs((int)tileSize.y), // Y position of the top-left corner of the tile in the spritesheet
		tileSize.x, // Width of the tile
		tileSize.y // Height of the tile
	};
	destRec = {
		position.x, // X position on the screen (change this as needed)
		position.y, // Y position on the screen (centered vertically)
		screenSize.x,             // Width of the tile on the screen
		screenSize.y              // Height of the tile on the screen
	};
	DrawTexturePro(texture, sourceRec, destRec, origin, rotation, color);
}
void TextureRenderer::Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation) {
	////TODO--> Update Texture By Time
	sourceRec = {
	   textureOffset.x * abs((int)tileSize.x), // X position of the top-left corner of the tile in the spritesheet
		textureOffset.y * abs((int)tileSize.y),  // Y position of the top-left corner of the tile in the spritesheet
		tileSize.x, // Width of the tile
		tileSize.y // Height of the tile
	};
	destRec = {
		position.x, // X position on the screen (change this as needed)
		position.y, // Y position on the screen (centered vertically)
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
void TextureRenderer::ChangeTileSize(Vector2 tileSize) {
	this->tileSize = tileSize;
}
void TextureRenderer::FlipX() {
	tileSize.x *= -1;
}
void TextureRenderer::FlipY() {
	tileSize.y *= -1;
}
void TextureRenderer::FlipX(bool flip) {
	if (flip)
		tileSize.x = -abs((int)tileSize.x);
	else
		tileSize.x = abs((int)tileSize.x);
}
void TextureRenderer::FlipY(bool flip) {
	if (flip)
		tileSize.y = -abs((int)tileSize.x);
	else
		tileSize.y = abs((int)tileSize.x);
}
bool TextureRenderer::IsFlippedX() {
	return tileSize.x < 0 ? true : false;
}
bool TextureRenderer::IsFlippedY() {
	return tileSize.y < 0 ? true : false;
}