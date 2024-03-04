#include "SpritePainter.hpp"
#include <math.h>

SpritePainter::SpritePainter() {

}
SpritePainter::SpritePainter(char* filePath, Vector2 tileSize, Vector2 origin) {
	_texture = LoadTexture(filePath);
    _tileSize = tileSize;
    _origin = origin;
}
SpritePainter::SpritePainter(Vector2 tileSize, Vector2 origin) {
    _tileSize = tileSize;
    _origin = origin;
}

void SpritePainter::Paint(Vector2 position, Vector2 textureOffset, Vector2 size, float rotation)
{
    ////TODO--> Update Texture By Time
    _sourceRec = {
        textureOffset.x* abs((int)_tileSize.x), // X position of the top-left corner of the tile in the spritesheet
        textureOffset.y* abs((int)_tileSize.y), // Y position of the top-left corner of the tile in the spritesheet
        _tileSize.x, // Width of the tile
        _tileSize.y // Height of the tile
    };
    _destRec = {
        position.x, // X position on the screen (change this as needed)
        position.y, // Y position on the screen (centered vertically)
        size.x,             // Width of the tile on the screen
        size.y              // Height of the tile on the screen
    };
	DrawTexturePro(_texture, _sourceRec, _destRec, _origin, rotation, _color);
}
void SpritePainter::Paint(Texture2D texture,Vector2 position, Vector2 textureOffset, Vector2 size, float rotation)
{
    ////TODO--> Update Texture By Time
    _sourceRec = {
       textureOffset.x* abs((int)_tileSize.x), // X position of the top-left corner of the tile in the spritesheet
        textureOffset.y* abs((int)_tileSize.y),  // Y position of the top-left corner of the tile in the spritesheet
        _tileSize.x, // Width of the tile
        _tileSize.y // Height of the tile
    };
    _destRec = {
        position.x, // X position on the screen (change this as needed)
        position.y, // Y position on the screen (centered vertically)
        size.x,             // Width of the tile on the screen
        size.y              // Height of the tile on the screen
    };
    DrawTexturePro(texture, _sourceRec, _destRec, _origin, rotation, _color);
}

void SpritePainter::ChangeColor(Color color) {
    _color = color;
}

void SpritePainter::FlipX() {
    _tileSize.x *= -1;
}
void SpritePainter::FlipY() {
    _tileSize.y *= -1;
}
void SpritePainter::FlipX(bool flip) {
    if (flip)
        _tileSize.x = -abs((int)_tileSize.x);
    else
        _tileSize.x = abs((int)_tileSize.x);
}
void SpritePainter::FlipY(bool flip) {
    if (flip)
        _tileSize.y = -abs((int)_tileSize.x);
    else
        _tileSize.y = abs((int)_tileSize.x);
}
