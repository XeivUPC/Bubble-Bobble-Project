#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "LevelManager.hpp"
#include <iostream>
using namespace std;

LevelManager::LevelManager(SystemCalls* calls, TileMapData* tileMapData, Level* activeLevel, Level* waitingLevel) {
	_calls = calls;
	_calls->renderCall.push_back(this);
	_calls->updateCall.push_back(this);
	_tileMapData = tileMapData;
	_activeLevel = activeLevel;
	_waitingLevel = waitingLevel;
}
void LevelManager::StartTransition()
{
	if (isOnTransition)
		return;
	isOnTransition = true;
	_waitingLevel->position = { 0, (float)GetScreenHeight() + _tileMapData->tileHeight*2 };
}
void LevelManager::EndTransition()
{
	isOnTransition = false;
	nextLevelIndex++;
	if(MAX_LEVELS>=nextLevelIndex)
		LoadNewWaitingLevel(nextLevelIndex);
}
void LevelManager::Update()
{
	if (!isOnTransition)
		return;

	_activeLevel->position = { 0,(_activeLevel->position.y -GetScreenHeight()/180.f)};
	_waitingLevel->position = { 0,(_waitingLevel->position.y - GetScreenHeight()/180.f)};


	if(_waitingLevel->position.y <=0)
	{
		*_activeLevel = *_waitingLevel;
		_activeLevel->position.y = 0;
		EndTransition();
	}
}
void LevelManager::Render() {
	_activeLevel->Render();
	if(isOnTransition)
		_waitingLevel->Render();
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
	(*_waitingLevel) = Level((char*)path, loadedLevelIndex, this);
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
	(*_activeLevel) = Level((char*)path, loadedLevelIndex, this);
}