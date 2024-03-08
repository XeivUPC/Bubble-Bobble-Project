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
#include "GameManager.hpp"




int main() {
    int screenWidth = 400;
    int screenHeight = 400;


    //// Important variables
    Level activeLevel;
    Level waitingLevel;
    ////

    InitWindow(screenWidth, screenHeight, "Bubble Bobble");

    InitAudioDevice();
    SetMasterVolume(0.1);

    Music music = LoadMusicStream("../Assets/Sounds/Music/01 Introduction Main Theme.ogg");
    PlayMusicStream(music);
    GameManager manager = GameManager();
    manager.activeLevel = &activeLevel;
    manager.waitingLevel = &waitingLevel;
    manager.levelManager->LoadNewActiveLevel(1);
    manager.levelManager->LoadNewWaitingLevel(2);
    
    
    SetWindowSize(manager.MAP_WIDTH * manager.TILE_WIDTH, (manager.MAP_HEIGHT-2) * manager.TILE_HEIGHT);
    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) / 2 - (manager.MAP_WIDTH * manager.TILE_WIDTH) / 2, GetMonitorHeight(GetCurrentMonitor()) / 2 - ((manager.MAP_HEIGHT) * manager.TILE_HEIGHT) / 2);


    TextUI((char*)"../Assets/UI/UI.json",&manager, manager.MAP_WIDTH, 2, 0, 0);
    TextUI puntuationUI = TextUI(nullptr,&manager, manager.MAP_WIDTH, 1, 0, 1);
    PuntuationManager puntuationManager = PuntuationManager(&manager, &manager.player1Points, &manager.player2Points, &manager.highScore, &puntuationUI);

    #pragma region SetControlFunctions

    auto updateFunc = [&]() {
         for (auto& obj : manager.calls.updateCall) {
            obj->Update();
        }
    };
    auto lateUpdateFunc = [&]() {
        for (auto& obj : manager.calls.lateUpdateCall) {
            obj->LateUpdate();
        }
    };
    auto renderFunc = [&]() {
        for (auto& obj : manager.calls.renderCall) {
            obj->Render();
        }
    };
    #pragma endregion

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {  
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateMusicStream(music);
        if(IsKeyPressed(KEY_ENTER))
            manager.levelManager->StartTransition();
        updateFunc();
        lateUpdateFunc();
        renderFunc();

        EndDrawing();
    }
    manager.SaveGameData(manager.highScore.GetPuntuation());
    CloseWindow();
    CloseAudioDevice(); 

    // Limpiar memoria
    manager.calls.Destroy();

    return 0;
}

