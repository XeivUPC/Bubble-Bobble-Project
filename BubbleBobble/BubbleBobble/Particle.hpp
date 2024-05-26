#pragma once
#include "Entity.hpp"
#include "AnimationRenderer.hpp"
#include "TextureManager.hpp"
#include "AudioManager.hpp"
#include "GameConfiguration.h"
#include "TilemapConfiguration.h"


class Particle : public Entity
{
public:
	Particle();
	virtual ~Particle();
	void Update() override;
	void Render() override;
	void Debug() override;
private:
};

