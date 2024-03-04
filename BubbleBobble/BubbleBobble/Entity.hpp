#pragma once
#include <raylib.h>
class Entity
{
public:
    virtual void Start();
    virtual void Awake();

    virtual void EarlyUpdate();
    virtual void Update();
    virtual void LateUpdate();
    
    virtual void Render();
    virtual void Destroy();
    virtual void Reset();

    Vector2 position = { (float)GetScreenWidth() / 2.f ,(float)GetScreenHeight() / 2.f };
    float rotation=0;

};