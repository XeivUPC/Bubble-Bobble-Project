#pragma once
#include "raylib.h"

#include "IRendereable.h"
#include "IUpdateable.h"
#include "IReseteable.h"
#include "IDebugeable.h"

#include "IActivable.h"
#include "ITimeable.h"
class Entity : public IRendereable, public IUpdateable, public IDebugeable, public IReseteable, public IActivable, public ITimeable
{
public:
	void Update() override {};
	void Render() override {};
	void Debug() override {};
	void Reset() override {};

	Vector2 position = { 0,0 };
	Vector2 direction = { 0,0 };
	float rotation;
	bool isActive = true;

protected:

};