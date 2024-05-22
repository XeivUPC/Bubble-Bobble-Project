#pragma once
#include "Enemy.hpp"
class SuperDrunk : public Enemy
{
public:
	SuperDrunk(Vector2 tilePos, int lookAt);
	~SuperDrunk();
	void Update() override;
	void Render() override;
	void Debug() override;
	void Brain() override;
	void CheckCollisions() override;
	Rectangle GetCollider() override;
	void Reset() override;

private:
	float speed;
};

