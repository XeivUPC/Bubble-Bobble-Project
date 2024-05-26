#pragma once
#include "Object.hpp"
class PowerUpObject : public Object
{
public:
	PowerUpObject(Vector2 tileIndex, Vector2 pos, int points, int powerUpIndex);
	~PowerUpObject();

	void Update() override;
	void Render() override;
	void Debug() override;
	void Reset() override;

	void CheckCollisions();

	void Use(Entity* user) override;



private:
	int pointValue;
	int powerUpIndex;
	Vector2 tileIndex{ 0,0 };
};
