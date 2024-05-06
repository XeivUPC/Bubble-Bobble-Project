#pragma once
#include "raylib.h"
#include "Renderer.hpp"
#include "Entity.hpp"

#include "IRendereable.h"
#include "IActivable.h"
class TilemapController : public IRendereable, public IActivable
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
	Renderer& ModifyRenderer();
	void SetTexture(Texture* texture);
	Vector2 GetDimensions();
	void Render() override;


private:
	int rowTiles;
	int* tilemap;
	Vector2 dimensions{ 0,0};
	Texture texture;
	Renderer renderer = Renderer(Vector2{ 8.f,8.f }, Vector2{ 0.f, 0.f }, Vector2{ 0.f, 0.f });
};

