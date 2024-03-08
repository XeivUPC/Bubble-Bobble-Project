#pragma once
#include <raylib.h>
class TextureRenderer
{
public:
	TextureRenderer();
	TextureRenderer(char* filePath, Vector2 tileSize, Vector2 origin);
	TextureRenderer(Vector2 tileSize, Vector2 origin);
	void Paint(Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation);
	void Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation);
	void ChangeColor(Color color);
	void ChangeOrigin(Vector2 origin);
	void ChangeTileSize(Vector2 tileSize);
	void FlipX();
	void FlipY();
	void FlipX(bool flip);
	void FlipY(bool flip);
	bool IsFlippedX();
	bool IsFlippedY();

private:
	Texture2D texture;
	Vector2 tileSize;
	Color color = WHITE;

	Rectangle sourceRec = {};
	Rectangle destRec = {};
	Vector2 origin = { 0,0 };
};

