#pragma once
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include "TextureRenderer.hpp"

struct Animation {
	Texture2D* texture;
	float delay;
	std::vector<Rectangle> frames;
};

class Renderer : public TextureRenderer
{
public:
	Renderer();
	~Renderer();

	///Anim
	void AddAnimation(const char* animID, Animation animationData);
	void PlayAniamtion(const char* animID);
	void PlayAniamtionForce(const char* animID);
	void UpdateAnimation();
	void Draw(float x, float y, int rotation, Color color);
	
	///Single


	/// Getters

private:
	bool IsAnimationLoaded(const char* animID);
	
	/// Variables
	std::unordered_map<const char*,Animation> animations;

	const char* currentAnim;
	int currentFrame;
	float currentDelay;
};



