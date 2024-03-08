#pragma once
#include "Entity.hpp"
#include "TextUI.hpp"
#include "SystemCalls.hpp"
#include "PuntuationHolder.hpp"
#include "GameManager.hpp"

class GameManager;
class PuntuationHolder;
class PuntuationManager : public Entity
{
public:
	PuntuationManager(GameManager* _gameManager,PuntuationHolder* p1, PuntuationHolder* p2, PuntuationHolder* highScore,TextUI* UI);
	void Update() override;
	int FromNumberToTile(int num);

private:
	PuntuationHolder* _p1;
	PuntuationHolder* _p2;
	PuntuationHolder* _highScore;
	TextUI* _UI;
	GameManager* _gm;
};

