#pragma once
#include "Entity.hpp"
#include "TextureRenderer.hpp"
#include "TilemapConfiguration.h"
class Object : public Entity
{
public:
	Object();
	~Object();

	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Reset() override;

	virtual void Use(Entity* user);

protected:
	TextureRenderer renderer = TextureRenderer(Vector2{ TILE_REAL_SIZE*2,TILE_REAL_SIZE*2}, Vector2{ 0.f, 0.f }, Vector2{ 0.f, 0.f });;
};


