#pragma once
#include <raylib.h>
class SpritePainter
{
public:
	SpritePainter();
	SpritePainter(char* filePath, Vector2 tileSize, Vector2 origin);
	SpritePainter(Vector2 tileSize,Vector2 origin);
	void Paint(Vector2 position, Vector2 textureOffset, Vector2 size, float rotation);
	void Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 size, float rotation);
	void ChangeColor(Color color);
	void FlipX();
	void FlipY();
	void FlipX(bool flip);
	void FlipY(bool flip);

private:
	Texture2D _texture;
	Vector2 _tileSize;
	Color _color = WHITE;

	Rectangle _sourceRec = {};
	Rectangle _destRec = {};
	Vector2 _origin = { 0,0 };

};