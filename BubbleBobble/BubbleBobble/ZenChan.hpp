#pragma once
#include "Enemy.hpp"

#define ZENCHAN_IA_RECALCULATION_TIME 3

class ZenChan : public Enemy
{
public:
	ZenChan(Vector2 tilePos, int lookAt);
	~ZenChan();
	void Update() override;
	void Render() override;
	void Debug() override;
	void Brain() override;
	void CheckCollisions() override;
	void Reset() override;
private:

	bool needsToGoUp = false;
	bool needsToGoDown = false;
	bool needsToGoLeft = false;

	bool canGoUp = false;
	bool canGoDown = false;

	float climbSpeed = TILE_SIZE * 8.f;
	float climbPoint;
	bool isClimbing = false;
	bool isWaitingClimbing = false;
	bool isGoingDown = false;

	float gravity = TILE_SIZE * 9.f;

	Vector2 speed;


	bool isGrounded = true;

};

