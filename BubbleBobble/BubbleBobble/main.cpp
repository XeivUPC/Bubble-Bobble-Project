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
    Image icon = LoadImage("Assets/Logo/Logo.png");
    SetWindowIcon(icon);
  

    //SetWindowSize(TILE_SIZE * GAME_TILE_WIDTH, TILE_SIZE * GAME_TILE_HEIGHT);

    SetTargetFPS(TARGET_FPS);
    SetMasterVolume(GAME_VOLUME);
    
    AudioManager& audioManager = AudioManager::Instance();
    GameController controller = GameController();

    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    //SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) / 2 - (TILE_SIZE * GAME_TILE_WIDTH) / 2, GetMonitorHeight(GetCurrentMonitor()) / 2 - (TILE_SIZE * GAME_TILE_HEIGHT) / 2);
    ToggleFullscreen();

    bool isMonitorHigher = GetMonitorHeight(GetCurrentMonitor()) > GetMonitorWidth(GetCurrentMonitor());
    int windowsSizeUsage = isMonitorHigher ? GetMonitorWidth(GetCurrentMonitor()) : GetMonitorHeight(GetCurrentMonitor());
    int tilemapSizeUsage = isMonitorHigher ? TILE_SIZE * GAME_TILE_WIDTH : TILE_SIZE * GAME_TILE_HEIGHT;
    int tilemapOffset = isMonitorHigher ? (TILE_SIZE * (GAME_TILE_HEIGHT + 0.5f)) : (TILE_SIZE * (GAME_TILE_WIDTH + 0.5f));
    float scale =(float)windowsSizeUsage / (tilemapSizeUsage);
    float offset = (tilemapSizeUsage) -tilemapOffset;
    if (offset > 0)
        offset = 0;

    Camera2D camera = { 0 };
    camera.target = { 0,0 };
    camera.offset = { -offset * scale * 2 , 0 };
    camera.rotation = 0.0f;
    camera.zoom = scale;


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        ////

        BeginMode2D(camera);
        controller.Update();
        audioManager.Update();  
        controller.Render();
        EndMode2D();

        ////

        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    printf("___________________________________\n");
    printf("\n");
    printf("DELETING DATA:\n");
    UnloadImage(icon);

    return 0;
}


