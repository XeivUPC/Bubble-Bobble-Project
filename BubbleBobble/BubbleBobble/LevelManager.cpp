#define _CRT_SECURE_NO_WARNINGS

#include "LevelManager.hpp"
#include "TextureManager.hpp"
#include "GameConfiguration.h"
#include <iostream>


LevelManager::LevelManager() {
	TextureManager::Instance().CreateTexture("Assets/Sprites/MapTileSet.png", "MapTileSet");
	TextureManager::Instance().CreateTexture("Assets/Sprites/MapShadowsTileSet.png", "MapShadowsTileSet");
}

void LevelManager::LoadNewWaitingLevel(int loadedLevelIndex)
{
	if (nextLevel != nullptr) {
		delete nextLevel;
		nextLevel = nullptr;
	}
	nextLevel = new Level(CreateFilePathName(loadedLevelIndex), loadedLevelIndex-1);
}

void LevelManager::LoadNewActiveLevel(int loadedLevelIndex)
{
	if (actualLevel != nullptr) {
		delete actualLevel;
		actualLevel = nullptr;
	}
	actualLevel = new Level(CreateFilePathName(loadedLevelIndex), loadedLevelIndex-1);
	actualLevel->LoadEnemies();
	actualLevel->LoadItems();
}

void LevelManager::Update() {
	if (!isOnTransition)
		return;

	actualLevel->position = { 0,(actualLevel->position.y - (GAME_TILE_HEIGHT * TILE_SIZE / transitionTime) * deltaTime) };
	nextLevel->position = { 0,(nextLevel->position.y - (GAME_TILE_HEIGHT * TILE_SIZE / transitionTime) * deltaTime) };


	if (nextLevel->position.y <= 0)
	{
		LoadNewActiveLevel(nextLevelIndex);
		actualLevel->position.y = 0;
		EndTransition();
	}
}

void LevelManager::Render() {
	actualLevel->Render();
	if (isOnTransition)
		nextLevel->Render();
}

void LevelManager::Debug()
{
	actualLevel->Debug();
	if (isOnTransition)
		nextLevel->Debug();
}

void LevelManager::Reset()
{
	LoadNewActiveLevel(1);
	LoadNewWaitingLevel(2);
	nextLevelIndex = 2;
}

bool LevelManager::IsOnTransition()
{
	return isOnTransition;
}

bool LevelManager::IsLastLevel()
{
	return !(MAX_LEVELS >= nextLevelIndex);
}

Level* LevelManager::GetActiveLevel()
{
	return actualLevel;
}

Level* LevelManager::GetNextLoadedLevel()
{
	return nextLevel;
}


Renderer* LevelManager::GetRenderer()
{
	return &renderer;
}

int LevelManager::GetActualLevelIndex()
{
	return actualLevel->GetLevelIndex();
}
int LevelManager::GetNextLevelIndex()
{
	return nextLevel->GetLevelIndex();
}

void LevelManager::StartTransition()
{
	if (isOnTransition || nextLevelIndex > MAX_LEVELS)
		return;
	isOnTransition = true;
	nextLevel->position = { 0,GAME_TILE_HEIGHT * TILE_SIZE };
}

void LevelManager::EndTransition()
{
	isOnTransition = false;
	nextLevelIndex++;
	if (MAX_LEVELS >= nextLevelIndex)
		LoadNewWaitingLevel(nextLevelIndex);
}

string LevelManager::CreateFilePathName(int levelToGetNamePath)
{
	string path = "Assets/Levels/Level";
	path += to_string(levelToGetNamePath);
	path += ".json";
	return path;
}

LevelManager::~LevelManager()
{
	delete actualLevel;
	delete nextLevel;
}