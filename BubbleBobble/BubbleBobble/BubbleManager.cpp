#include "BubbleManager.hpp"
#include "TextureManager.hpp"

BubbleManager::BubbleManager() {
	TextureManager::Instance().CreateTexture("../Assets/Sprites/Bubble.png", "BubbleTileSet");

	bubblesPool = new Bubble[MAX_BUBBLES_POOL];
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		bubblesPool[i].isActive = false;
	}
}
BubbleManager::~BubbleManager()
{
	delete[] bubblesPool;
}

void BubbleManager::Update()
{
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		if (bubblesPool[i].isActive)
			bubblesPool[i].Update();
	}
}

void BubbleManager::Render()
{
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		if (bubblesPool[i].isActive)
			bubblesPool[i].Render();
	}
}

void BubbleManager::RenderDebug()
{
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		if (bubblesPool[i].isActive)
			bubblesPool[i].RenderDebug();
	}
}

void BubbleManager::DisableAll()
{
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		bubblesPool[i].isActive = false;
	}
}

Bubble* BubbleManager::GetBubble()
{
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		if (!bubblesPool[i].isActive) {
			return &bubblesPool[i];
		}
	}
	return nullptr;
}

Bubble* BubbleManager::GetBubbleByIndex(int index)
{
	return &bubblesPool[index];
}

void BubbleManager::MoveBubbleToFront(Bubble* bubble)
{
	for (size_t i = 0; i < MAX_BUBBLES_POOL; i++)
	{
		if (&bubblesPool[i] == bubble) {
			Bubble aux = *bubble;
			for (size_t x = i; x < MAX_BUBBLES_POOL-1; x++)
			{
				bubblesPool[x] = bubblesPool[x + 1];
			}
			bubblesPool[MAX_BUBBLES_POOL-1] = aux;
			break;
		}
	}
}
