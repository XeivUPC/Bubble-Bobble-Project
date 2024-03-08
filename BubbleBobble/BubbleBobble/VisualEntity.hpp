#pragma once
#include "Entity.hpp"
#include "TextureRenderer.hpp"
class VisualEntity : public Entity
{
public:
	void Update() override;
	void LateUpdate() override;

	void Render() override;
	void Reset() override;
	TextureRenderer renderer;
	Vector2 textureOffset = { 0,0 };
};

