#pragma once
#include "Object.hpp"
class Fruit : public Object
{
public:
	Fruit(Vector2 tileIndex, Vector2 pos, int points);
	~Fruit();

	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Reset() override;

	void CheckCollisions();

	void Use(Entity* user) override;



private:
	int pointValue;
	Vector2 tileIndex{0,0};
};

