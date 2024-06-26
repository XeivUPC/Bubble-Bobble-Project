#pragma once
#include "raylib.h"
#include "Entity.hpp"
#include "Bubble.hpp"
#define MAX_BUBBLES_POOL  100



#include "IRendereable.h"
#include "IUpdateable.h"
#include "IDebugeable.h"
#include "IReseteable.h"
class BubbleManager : public IRendereable, public IUpdateable, public IDebugeable, public IReseteable
{

public:

    static BubbleManager& Instance()
    {
        static BubbleManager instance; //Guaranteed to be initialized only once
        return instance;
    }
    void Update() override;
    void Render() override;
    void Debug() override;
    void Reset() override;
    void DisableAll();
    void PopAll();
    int GetBubbleAmount();
    Bubble* GetBubble();
    Bubble* GetBubbleByIndex(int index);
    void MoveBubbleToFront(Bubble* bubble);

private:
    //Private constructor to prevent instantiation
    BubbleManager();
    //Destructor
    ~BubbleManager();
    Bubble* bubblesPool = nullptr;
};

