#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include "raylib.h"

#include "SystemCalls.hpp"
#include "LevelManager.hpp"
#include "TileMapData.hpp"
#include "Level.hpp"
#include "TextUI.hpp"
#include "PuntuationManager.hpp"
#include "Player.hpp"

void SaveGameData(int highScore) 
{
    FILE* file;
    file = fopen("../Assets/SaveData/HighScore.txt","w");
    fprintf(file, "%d",highScore);
    fclose(file);
}
void LoadGameData(int* highScore)
{
    FILE* file;
    file = fopen("../Assets/SaveData/HighScore.txt", "r");
    fscanf(file, "%d", highScore);
    fclose(file);
}

int main() {
    int screenWidth = 400;
    int screenHeight = 400;


    //// Important variables
    int player1Points = 0;
    int player2Points = 0;
    int highScore = 0;

    Level activeLevel;
    Level waitingLevel;
    ////

    LoadGameData(&highScore);
    InitWindow(screenWidth, screenHeight, "Bubble Bobble");
    
    SystemCalls calls = SystemCalls();
    TileMapData tileMapData = TileMapData();
    
    SetWindowSize(tileMapData.tileMapWidth*tileMapData.tileWidth, tileMapData.tileMapHeight * tileMapData.tileHeight);
    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor())/2 - (tileMapData.tileMapWidth * tileMapData.tileWidth)/2, GetMonitorHeight(GetCurrentMonitor()) /2 - (tileMapData.tileMapHeight * tileMapData.tileHeight)/2);

    #pragma region  Levels
    LevelManager levelManager = LevelManager(&calls, &tileMapData, &activeLevel, &waitingLevel);
    levelManager.LoadNewActiveLevel(1);
    levelManager.LoadNewWaitingLevel(2);
    #pragma endregion

    TextUI((char*)"../Assets/UI/UI.json", &calls, &tileMapData, tileMapData.tileMapWidth, 2, 0, 0);

    TextUI puntuationUI = TextUI(nullptr, &calls, &tileMapData, tileMapData.tileMapWidth, 1, 0, 1);
    PuntuationManager puntuationManager = PuntuationManager(&player1Points, &player2Points, &highScore, &calls, &puntuationUI);

    Player player = Player(&calls, &tileMapData);
    InitAudioDevice();
    SetMasterVolume(100);

    #pragma region SetControlFunctions
    auto earlyUpdateFunc = [&]() {
         for (auto& obj : calls.earlyUpdateCall) {
            obj->EarlyUpdate();
        }
    };
    auto updateFunc = [&]() {
         for (auto& obj : calls.updateCall) {
            obj->Update();
        }
    };
    auto lateUpdateFunc = [&]() {
        for (auto& obj : calls.lateUpdateCall) {
            obj->LateUpdate();
        }
    };
    auto renderFunc = [&]() {
        for (auto& obj : calls.renderCall) {
            obj->Render();
        }
    };
    #pragma endregion

    SetTargetFPS(60);
    while (!WindowShouldClose()) {  
        BeginDrawing();
        ClearBackground(BLACK);


        if(IsKeyPressed(KEY_ENTER))
            levelManager.StartTransition();
        earlyUpdateFunc();
        updateFunc();
        lateUpdateFunc();
        renderFunc();

        EndDrawing();
    }
    SaveGameData(highScore);
    CloseWindow();
    CloseAudioDevice(); 

    // Limpiar memoria
    calls.Destroy();

    return 0;
}

