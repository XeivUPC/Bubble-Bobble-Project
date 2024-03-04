#pragma once
#include "Entity.hpp"
#include "TextUI.hpp"
#include "SystemCalls.hpp"

class PuntuationManager : public Entity
{
public:
	PuntuationManager(int* p1, int* p2, int* highScore, SystemCalls* calls,TextUI* UI);
	void Update() override;
	int FromNumberToTile(int num);

private:
	int* _p1;
	int* _p2;
	int* _highScore;
	TextUI* _UI;
	SystemCalls* _calls;
};

