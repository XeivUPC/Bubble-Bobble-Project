#pragma once
#include "Entity.hpp"
#include "Renderer.hpp"
#include "TilemapConfiguration.h"
class Object : public Entity
{
public:
	Object();
	~Object();

	void Update() override;
	void Render() override;
	void Debug() override;
	void Reset() override;

	virtual void Use(Entity* user);

protected:
	Renderer renderer = Renderer(Vector2{ TILE_REAL_SIZE*2,TILE_REAL_SIZE*2}, Vector2{ 0.f, 0.f }, Vector2{ 0.f, 0.f });;
};


