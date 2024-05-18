#pragma once
#include "Level.hpp"
#include "Renderer.hpp"
#include "TilemapConfiguration.h"
#include <string>

using namespace std;
#define MAX_LEVELS  9


#include "IRendereable.h"
#include "IUpdateable.h"
#include "IReseteable.h"
#include "IDebugeable.h"
class LevelManager : public IRendereable, public IUpdateable, public IDebugeable, public IReseteable
{ 
public:
    static LevelManager& Instance()
    {
        static LevelManager instance; //Guaranteed to be initialized only once
        return instance;
    }
    void Update() override;
    void Render() override;
    void Debug() override;
    void Reset() override;
    void StartTransition();
    void LoadNewWaitingLevel(int loadedLevelIndex);
    void LoadNewActiveLevel(int loadedLevelIndex);
    bool IsOnTransition();
    bool IsLastLevel();
    Level* GetActiveLevel();
    Level* GetNextLoadedLevel();
    Renderer* GetRenderer();
    int GetActualLevelIndex();

private:
    //Private constructor to prevent instantiation
    LevelManager();
    //Destructor
    ~LevelManager();

    void EndTransition();

    string CreateFilePathName(int levelToGetNamePath);

    Level* actualLevel = nullptr;
    Level* nextLevel = nullptr;

    Renderer renderer = Renderer(Vector2{ TILE_REAL_SIZE,TILE_REAL_SIZE }, Vector2{ 0.f, 0.f }, Vector2{ 0.f, 0.f });
    
    int nextLevelIndex = 2;
    bool isOnTransition = false;
    float transitionTime = 2;
};

