#pragma once
#include "raylib.h"
class Entity
{
public:
    virtual void Update();
    virtual void LateUpdate();
    virtual void Destroy();
    virtual void Render();
    virtual void Reset();

    ////// Variables
    Vector2 position = { (float)GetScreenWidth() / 2.f ,(float)GetScreenHeight() / 2.f };
    float rotation = 0;
    bool isActive = false;
};