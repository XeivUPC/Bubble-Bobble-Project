#include "FruitObject.hpp"
#include "ObjectsManager.hpp"
#include "TextureManager.hpp"
#include "AudioManager.hpp"
#include "Player.hpp"
#include "PointParticle.hpp"

FruitObject::FruitObject(Vector2 tileIndex, Vector2 pos, int points)
{
	TextureManager::Instance().CreateTexture("Assets/Sprites/Items.png", "ItemsSpriteSheet");
	AudioManager::Instance().CreateSound("Assets/Sounds/SFX/TakeFood.wav","EatFruit");
	position = pos;
	this->tileIndex = tileIndex;
	pointValue = points;
}

FruitObject::~FruitObject()
{
}

void FruitObject::Update()
{
	CheckCollisions();
}

void FruitObject::Render()
{
	renderer.Paint(*TextureManager::Instance().GetTexture("ItemsSpriteSheet"), Vector2{position.x-TILE_SIZE,position.y-TILE_SIZE *2}, Vector2{ tileIndex.x,tileIndex.y }, { TILE_SIZE * 2,TILE_SIZE * 2 }, 0);
}

void FruitObject::Debug()
{
	DrawRectangle(position.x - TILE_SIZE * 0.8, position.y - TILE_SIZE * 1.7, TILE_SIZE * 0.8 * 2, TILE_SIZE * 0.8 * 2, { 255,255,255,100 });
	DrawCircle(position.x, position.y, 3, BLUE);
}

void FruitObject::Reset()
{
}

void FruitObject::CheckCollisions()
{
	Rectangle collision = { position.x - TILE_SIZE * 0.8, position.y - TILE_SIZE * 1.7, TILE_SIZE * 0.8 * 2, TILE_SIZE * 0.8 * 2 };

	for (size_t i = 0; i < ObjectsManager::Instance().GetCollectorsAmount(); i++)
	{
		Entity* x = ObjectsManager::Instance().GetCollectors(i);
		Player* player = dynamic_cast<Player*>(x);
		if (player != nullptr && player->isActive) {

			if (CheckCollisionRecs(collision, player->GetCollision())) {
				Use(x);
			}
		}
	}
}

void FruitObject::Use(Entity* user)
{
	ParticleManager::Instance().AddParticle(new PointParticle({position.x-TILE_SIZE/2, position.y -TILE_SIZE}, pointValue));
	Player* player = dynamic_cast<Player*>(user);
	player->puntuationController->ModifyPuntutation(pointValue);
	ObjectsManager::Instance().RemoveObject(this);
	AudioManager::Instance().PlaySoundByName("EatFruit");

}
