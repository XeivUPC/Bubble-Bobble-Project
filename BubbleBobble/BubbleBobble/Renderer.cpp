#include "Renderer.hpp"
#include "TilemapConfiguration.h"
#include "GameConfiguration.h"
#include <iostream>
#include <math.h>
Renderer::Renderer()
{

}

Renderer::~Renderer()
{
}


void Renderer::AddAnimation(const char* animID, Animation animationData)
{
	if (IsAnimationLoaded(animID))
	{
		printf("Animation Already Added");
		return;
	}
	animations[animID] = animationData;
}

void Renderer::PlayAniamtion(const char* animID) {
    if (!IsAnimationLoaded(animID))
    {
        printf("Animation Is Not Added");
        return;
    }
    if (animID == currentAnim)
        return;
    currentAnim = animID;
    currentFrame = 0;
    currentDelay = animations[currentAnim].delay;
}

void Renderer::PlayAniamtionForce(const char* animID)
{
    if (!IsAnimationLoaded(animID))
    {
        printf("Animation Is Not Added");
        return;
    }
    currentAnim = animID;
    currentFrame = 0;
    currentDelay = animations[currentAnim].delay;
}

void Renderer::UpdateAnimation()
{
    if (currentDelay > 0)
    {
        currentDelay-=deltaTime;
        if (currentDelay < 0)
        {
            currentFrame++;
            currentFrame %= animations[currentAnim].frames.size();
            currentDelay = animations[currentAnim].delay;
        }
    }
}

void Renderer::Draw(float x, float y, int rotation, Color color)
{
    sourceRec = {
        animations[currentAnim].frames[currentFrame].x, // X position of the top-left corner of the tile in the spritesheet
        animations[currentAnim].frames[currentFrame].y, // Y position of the top-left corner of the tile in the spritesheet
        animations[currentAnim].frames[currentFrame].width * flippedValueX, // Width of the tile
        animations[currentAnim].frames[currentFrame].height * flippedValueY // Height of the tile
    };
    destRec = {
        x, // X position on the screen (change this as needed)
        y, // Y position on the screen (centered vertically)
        abs(animations[currentAnim].frames[currentFrame].width) * TILE_SCALE_FACTOR,             // Width of the tile on the screen
         abs(animations[currentAnim].frames[currentFrame].height) * TILE_SCALE_FACTOR            // Height of the tile on the screen
    };

    DrawTexturePro(*animations[currentAnim].texture, sourceRec, destRec, Vector2{ 0,0 }, rotation, color);
}

bool Renderer::IsAnimationLoaded(const char* animID)
{
	return animations.find(animID) != animations.end();
}

