#pragma once
#include "Object.hpp"
class FruitObject : public Object
{
public:
	FruitObject(Vector2 tileIndex, Vector2 pos, int points);
	~FruitObject();

	void Update() override;
	void Render() override;
	void Debug() override;
	void Reset() override;

	void CheckCollisions();

	void Use(Entity* user) override;



private:
	int pointValue;
	Vector2 tileIndex{0,0};
};

