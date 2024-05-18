#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "raylib.h"
#include "TilemapConfiguration.h"
#include "GameConfiguration.h"
#include "AudioManager.hpp"
#include "GameController.hpp"

#include "MemLeaks.h"
int main() {
    ReportMemoryLeaks();

    int screenWidth = 400;
    int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Bubble Bobble");
    InitAudioDevice();
    SetWindowIcon(LoadImage("Assets/Logo/Logo.png"));

    SetWindowSize(TILE_SIZE * GAME_TILE_WIDTH, TILE_SIZE * GAME_TILE_HEIGHT);
    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) / 2 - (TILE_SIZE * GAME_TILE_WIDTH) / 2, GetMonitorHeight(GetCurrentMonitor()) / 2 - (TILE_SIZE * GAME_TILE_HEIGHT) / 2);

    SetTargetFPS(TARGET_FPS);
    SetMasterVolume(GAME_VOLUME);

    AudioManager& audioManager = AudioManager::Instance();
    GameController controller = GameController();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        ////

        controller.Update();
        audioManager.Update();
        controller.Render();

        ////

        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    printf("___________________________________\n");
    printf("\n");
    printf("DELETING DATA:\n");

    return 0;
}

