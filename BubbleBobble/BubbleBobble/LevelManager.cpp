#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "LevelManager.hpp"
#include <iostream>
using namespace std;

LevelManager::LevelManager(GameManager* gameManager) {
	_gm = gameManager;
	_gm->calls.updateCall.push_back(this);
	_gm->calls.renderCall.push_back(this);
}
void LevelManager::StartTransition()
{
	if (isOnTransition)
		return;
	isOnTransition = true;
	_gm->player->SetStatus(1);
	_gm->waitingLevel->position = { 0, (float)GetScreenHeight() + _gm->TILE_HEIGHT*2 };
}
void LevelManager::EndTransition()
{
	isOnTransition = false;
	nextLevelIndex++;
	if(MAX_LEVELS>=nextLevelIndex)
		LoadNewWaitingLevel(nextLevelIndex);
	_gm->player->SetStatus(0);
}
void LevelManager::Update()
{
	if (!isOnTransition)
		return;

	_gm->activeLevel->position = { 0,(_gm->activeLevel->position.y -GetScreenHeight()/180.f)};
	_gm->waitingLevel->position = { 0,(_gm->waitingLevel->position.y - GetScreenHeight()/180.f)};


	if(_gm->waitingLevel->position.y <=0)
	{
		*_gm->activeLevel = *_gm->waitingLevel;
		_gm->activeLevel->position.y = 0;
		EndTransition();
	}
}
void LevelManager::Render() {
	_gm->activeLevel->Render();
	if(isOnTransition)
		_gm->waitingLevel->Render();
}
void LevelManager::LoadNewWaitingLevel(int loadedLevelIndex)
{
	char integer_String[32];
	sprintf(integer_String, "%d", loadedLevelIndex);
	char path[100] = "../Assets/Levels/Level";
	char end[6] = ".json";
	strcat(path, integer_String);
	strcat(path, end);
	loadedLevelIndex--;
	(*_gm->waitingLevel) = Level((char*)path, loadedLevelIndex, _gm);
}
void LevelManager::LoadNewActiveLevel(int loadedLevelIndex)
{
	char integer_String[32];
	sprintf(integer_String, "%d", loadedLevelIndex);
	char path[100] = "../Assets/Levels/Level";
	char end[6] = ".json";
	strcat(path, integer_String);
	strcat(path, end);
	loadedLevelIndex--;
	(*_gm->activeLevel) = Level((char*)path, loadedLevelIndex, _gm);
}