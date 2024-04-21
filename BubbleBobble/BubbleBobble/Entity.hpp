#pragma once
#include "raylib.h"

class Entity
{
public:

	virtual void Update();
	virtual void Render();
	virtual void RenderDebug();
	virtual void Reset();

	Vector2 position = { 0,0 };
	Vector2 direction = { 0,0 };
	float rotation;
	bool isActive = true;

protected:
	float internalTimer = 0;
};