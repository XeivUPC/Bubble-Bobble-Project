#pragma once
#include <raylib.h>
class Renderer
{
public:
	Renderer();
	Renderer(Vector2 tileSize, Vector2 origin, Vector2 displacement);
	~Renderer();
	void Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation);
	void Paint(Texture2D texture, Vector2 position, Vector2 textureOffset, Vector2 screenSize, float rotation, Color color);
	void ChangeColor(Color color);
	void ChangeOrigin(Vector2 origin);
	void ChangeDisplacement(Vector2 displacement);
	void ChangeTileSize(Vector2 tileSize);
	void FlipX();
	void FlipY();
	void FlipX(bool flip);
	void FlipY(bool flip);
	bool IsFlippedX();
	bool IsFlippedY();
	int GetFlippedXValue();
	int GetFlippedYValue();
	bool isActive = true;
private:
	Vector2 tileSize;
	Color color = WHITE;

	
	Vector2 origin = { 0,0 };
protected:
	Vector2 displacement = { 0,0 };
	Rectangle sourceRec = {};
	Rectangle destRec = {};
	int flippedValueX = 1;
	int flippedValueY = 1;
	
};

