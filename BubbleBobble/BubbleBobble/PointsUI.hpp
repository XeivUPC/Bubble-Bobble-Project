#pragma once
#include "Entity.hpp"
#include "TilemapController.hpp"
#include "PuntuationHolder.hpp"

class PointsUI : public Entity
{
public:
	PointsUI(PuntuationHolder* points, TilemapController* UI);
	void Update() override;
	int FromNumberToTile(int num);

private:
	PuntuationHolder* points;
	TilemapController* UI;
};

