#pragma once
#include "Level.hpp"
#include "TextureRenderer.hpp"
#include "TilemapConfiguration.h"
#include <string>

using namespace std;
#define MAX_LEVELS  8
class LevelManager : public Entity
{ 
public:
    static LevelManager& Instance()
    {
        static LevelManager instance; //Guaranteed to be initialized only once
        return instance;
    }
    void Update() override;
    void Render() override;
    void Reset() override;
    void LoadNewWaitingLevel(int loadedLevelIndex);
    void LoadNewActiveLevel(int loadedLevelIndex);
    bool IsOnTransition();
    Level* GetActiveLevel();
    Level* GetNextLoadedLevel();
    TextureRenderer* GetRenderer();

private:
    //Private constructor to prevent instantiation
    LevelManager();
    //Destructor
    ~LevelManager();

    void StartTransition();
    void EndTransition();

    string CreateFilePathName(int levelToGetNamePath);

    Level* actualLevel = nullptr;
    Level* nextLevel = nullptr;

    TextureRenderer renderer = TextureRenderer(Vector2{ TILE_REAL_SIZE,TILE_REAL_SIZE }, Vector2{ 0.f, 0.f }, Vector2{ 0.f, 0.f });
    
    int nextLevelIndex = 2;
    bool isOnTransition = false;
    float transitionTime = 2;
};

