#include "Enemy.hpp"
#include "EnemyManager.hpp"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::Render()
{
}
void Enemy::Debug()
{
}

void Enemy::Reset()
{
}

bool Enemy::TryToBubble(bool player1bubble)
{
	if (!canBeInsideBubble)
		return false;
	if (isInsideBubble)
		return false;
	isInsideBubble = true;
	player1Bubble = player1bubble;
	return true;
}

void Enemy::RemoveFromBubble()
{
	isInsideBubble = false;
}

bool Enemy::IsInsideBubble()
{
	return isInsideBubble;
}

void Enemy::SetBubbleTime(float time)
{
	bubbleTime = time;
}

void Enemy::Brain()
{
}

void Enemy::SearchTargetTile()
{
	Entity* target=nullptr;
	EnemyManager& enemyManager = EnemyManager::Instance();


	if (enemyManager.targets.size() == 0)
		return;
	if (retargetTimer > RETARGET_TIME || currentTarget==nullptr || !currentTarget->isActive) {

		for (size_t i = 0; i < enemyManager.targets.size(); i++)
		{
			if (enemyManager.targets[i]->isActive) {
				target = enemyManager.targets[i];
				break;
			}
		}

		if (target == nullptr) {
			currentTarget = enemyManager.targets[0];
			return;
		}


		float minDistance = sqrt(pow((position.x - target->position.x), 2) + std::pow((position.y - target->position.y), 2));
		for (size_t i = 0; i < enemyManager.targets.size(); i++)
		{
			if (!enemyManager.targets[i]->isActive)
				continue;
			float dist = sqrt(pow((position.x - enemyManager.targets[i]->position.x), 2) + std::pow((position.y - enemyManager.targets[i]->position.y), 2));
			if (dist < minDistance) {
				minDistance = dist;
				target = enemyManager.targets[i];
			}
		}
		if (currentTarget != target) {
			retargetTimer = 0;
			currentTarget = target;
		}
	}
	
}

void Enemy::CheckCollisions()
{
}

Rectangle Enemy::GetCollider()
{
	return Rectangle{0,0,0,0};
}

int Enemy::GetPoints()
{
	return pointsToGive;
}

void Enemy::DrawDebug()
{
}
