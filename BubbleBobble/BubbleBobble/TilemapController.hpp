#pragma once
#include "raylib.h"
#include "TextureRenderer.hpp"
#include "Entity.hpp"

class TilemapController : public Entity
{
public:

	TilemapController(Texture* texture, const char* path, int tilesXRow, Vector2 dimensions);
	TilemapController( const char* path, int tilesXRow, Vector2 dimensions);
	~TilemapController();

	bool LoadFromJson(const char* path);
	void ModifyTile(int index, int newValue);
	void ModifyTile(int x, int y, int newValue);
	void ModifyTile(Vector2 position, int newValue);
	int GetTile(int index);
	int GetTile(int x, int y);
	int GetTile(Vector2 position);
	TextureRenderer& ModifyRenderer();
	void SetTexture(Texture* texture);
	Vector2 GetDimensions();
	void Render() override;


private:
	int rowTiles;
	int* tilemap;
	Vector2 dimensions{ 0,0};
	Texture texture;
	TextureRenderer renderer = TextureRenderer(Vector2{ 8.f,8.f }, Vector2{ 0.f, 0.f }, Vector2{ 0.f, 0.f });
};

