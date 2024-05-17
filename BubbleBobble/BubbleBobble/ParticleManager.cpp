#include "ParticleManager.hpp"

ParticleManager::ParticleManager()
{
	TextureManager::Instance().CreateTexture("Assets/Sprites/BasicParticles.png", "BasicParticlesTileset");
}

ParticleManager::~ParticleManager()
{
	DestroyAll();
}

void ParticleManager::Update()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->Update();
	}
}

void ParticleManager::Render()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->Render();
	}
}

void ParticleManager::Debug()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->Debug();
	}
}

void ParticleManager::AddParticle(Particle* newParticle)
{
	particles.push_back(newParticle);
}

void ParticleManager::RemoveParticle(Particle* particleToRemove)
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i] == particleToRemove) {
			particles.erase(particles.begin() + i);
			break;
		}
	}
	delete particleToRemove;
	particleToRemove = nullptr;
}

void ParticleManager::DestroyAll()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}
	particles.clear();
}
