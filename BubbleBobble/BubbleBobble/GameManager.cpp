#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "GameManager.hpp"


GameManager::GameManager()
{
	levelManager = new LevelManager(this);
    player = new Player(this);
    int valueInit = 0;
    int* loaderData = &valueInit;
    LoadGameData(loaderData);
    highScore.SetPuntutation(*loaderData);
}

void GameManager::SaveGameData(int highScore)
{
    FILE* file;
    file = fopen("../Assets/SaveData/HighScore.txt", "w");
    fprintf(file, "%d", highScore);
    fclose(file);
}
void GameManager::LoadGameData(int* highScore)
{
    FILE* file;
    file = fopen("../Assets/SaveData/HighScore.txt", "r");
    fscanf(file, "%d", highScore);
    fclose(file);
}
