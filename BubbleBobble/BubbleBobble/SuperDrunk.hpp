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
	void Hit(int amountDamage) override;
	bool TryKill() override;
	void CheckCollisions() override;
	Rectangle GetCollider() override;
	void Reset() override;

private:
	bool MoveToSpawnPoint();
	float speed;
	bool hasBeenHit = false;
	#define HIT_RENDER 0.1
	Vector2 spawnPoint;
};

