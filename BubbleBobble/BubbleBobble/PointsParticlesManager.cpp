#include "PointsParticlesManager.hpp"
#include "TextureManager.hpp"


void PointsParticlesManager::Update()
{
	for (size_t i = 0; i < MAX_POINTS_PARTICLES_POOL; i++)
	{
		if (pointsParticlesPool[i].isActive)
			pointsParticlesPool[i].Update();
	}
}

void PointsParticlesManager::Render()
{
	for (size_t i = 0; i < MAX_POINTS_PARTICLES_POOL; i++)
	{
		if (pointsParticlesPool[i].isActive)
			pointsParticlesPool[i].Render();
	}
}

void PointsParticlesManager::Debug()
{
	for (size_t i = 0; i < MAX_POINTS_PARTICLES_POOL; i++)
	{
		if (pointsParticlesPool[i].isActive)
			pointsParticlesPool[i].Debug();
	}
}

void PointsParticlesManager::DisableAll()
{
	for (size_t i = 0; i < MAX_POINTS_PARTICLES_POOL; i++)
	{
		pointsParticlesPool[i].isActive = false;
	}
}

PointParticle* PointsParticlesManager::GetPointParticle()
{
	for (size_t i = 0; i < MAX_POINTS_PARTICLES_POOL; i++)
	{
		if (!pointsParticlesPool[i].isActive) {
			return &pointsParticlesPool[i];
		}
	}
	return nullptr;
}

PointsParticlesManager::~PointsParticlesManager()
{
	delete[] pointsParticlesPool;
}

PointsParticlesManager::PointsParticlesManager() 
{
	TextureManager::Instance().CreateTexture("../Assets/Sprites/Points.png", "PointsParticlesTileSet");

	pointsParticlesPool = new PointParticle[MAX_POINTS_PARTICLES_POOL];
	for (size_t i = 0; i < MAX_POINTS_PARTICLES_POOL; i++)
	{
		pointsParticlesPool[i].isActive = false;
	}
}
