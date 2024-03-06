#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player(SystemCalls* calls, TileMapData* tileMapData, LevelManager* levelManager) {
	_calls = calls;
	_tileMapData = tileMapData;
	_levelManager = levelManager;
	_calls->updateCall.push_back(this);
	_calls->renderCall.push_back(this);
	_calls->destroyCall.push_back(this);
	painter = SpritePainter(Vector2{ -16,16 }, Vector2{ (float)_tileMapData->tileWidth ,(float)_tileMapData->tileHeight * 2 });
	position = { (float)_tileMapData->tileWidth * 3 ,(float)_tileMapData->tileHeight * 27 };
}
void Player::Update() {

	GetInput();
	
	CheckCollisions();

	Move();


	
}
void Player::GetInput() {


	if (IsKeyDown(KEY_D)) {
		_direction.x = _speed;
		if (!isGrounded) {
			if (isJumping) {
				_direction.x = _airSpeed * 2.1;
			}
			else {
				_direction.x = _airSpeed/1.5;
			}
		}
		
		painter.FlipX(true);
	}
	else if (IsKeyDown(KEY_A)) {
		_direction.x = -_speed;
		if (!isGrounded) {
			if (isJumping) {
				_direction.x = -_airSpeed * 2.1;
			}
			else {
				_direction.x = -_airSpeed/1.5;
			}
			
		}
		painter.FlipX(false);
	}
	else {
		_direction.x = 0;
	}
	
	if (IsKeyPressed(KEY_SPACE) && isGrounded && !isJumping) {
		isJumping = true;
		isFalling = false;
		_jumpDistance = 0;
		_jumpSpeed = _jumpInitialSpeed;
	}

	_direction.y = _gravity; //g
	if (isJumping)
		Jump();


	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isShooting && isGrounded) {
		isShooting = true;
		xOffset = 0;
	}

}
void Player::Move() {

	position.x += _direction.x * _tileMapData->tileHeight / 30;;
	position.y += _direction.y * _tileMapData->tileHeight / 30;;
}

void Player::Jump() {
	_jumpDistance += abs(_jumpSpeed);
	if (isFalling) {
		_direction.y = -_jumpSpeed;
		_jumpSpeed -= 0.4;
		if (abs(_jumpSpeed) > _jumpMaxSpeed)
			_jumpSpeed = -_jumpMaxSpeed;
		if (_jumpDistance >= _jumpHeight || isGrounded) {
			isFalling = false;
			isJumping = false;
		}
	}
	else {
		_direction.y = -_jumpSpeed;
		_jumpSpeed -= 0.07;
		if (abs(_jumpSpeed) > _jumpMaxSpeed)
			_jumpSpeed = -_jumpMaxSpeed;
		if (_jumpDistance >= _jumpHeight) {
			isFalling = true;
			_jumpDistance = 0;
			_jumpSpeed /= 2;
		}
	}
}

void Player::CheckCollisions() {
	Vector2 newDir = _direction;
	Level level = *_levelManager->_activeLevel;

#pragma region Colliders
	Rectangle PlayerCollisionBottom = { position.x - (_tileMapData->tileWidth) * 0.8, position.y, _tileMapData->tileWidth * 1.6, _tileMapData->tileHeight * 0.1 };
	Rectangle PlayerCollisionLeft = { position.x - (_tileMapData->tileWidth) - _tileMapData->tileWidth * 0.1, position.y - _tileMapData->tileHeight * 1.5, _tileMapData->tileWidth * 0.1 , _tileMapData->tileHeight * 1 };
	Rectangle PlayerCollisionRight = { position.x + (_tileMapData->tileWidth), position.y - _tileMapData->tileHeight * 1.5, _tileMapData->tileWidth * 0.1 , _tileMapData->tileHeight * 1 };

	int Offset = - _tileMapData->tileWidth * 0.1f;
	Rectangle PlayerCollision = { position.x - (_tileMapData->tileWidth) + Offset ,position.y - (_tileMapData->tileHeight * 2) + Offset, _tileMapData->tileWidth * 2 - Offset * 2, _tileMapData->tileHeight * 2 - Offset * 2 };
#pragma endregiond

	float xPoint = (float)floor(position.x) / _levelManager->_tileMapData->tileWidth;
	float yPoint = (float)floor(position.y - _levelManager->_tileMapData->tileHeight / 2) / _levelManager->_tileMapData->tileHeight;

	bool isFullWall = false;
	bool checkMoreAxisX = true;
	isGrounded = false;

	for (int y = yPoint - 3; y < yPoint + 3; y++)
	{
		Vector2 yTileDataPosition = { (y)*_levelManager->_tileMapData->tileHeight ,_levelManager->_tileMapData->tileHeight };
		for (int x = xPoint - 3; x < xPoint + 3; x++)
		{

			if (level.IsTile(x, y, level.Collisions)) {
				int tileCollisionData = level.GetTile(x, y, level.Collisions);
				Vector2 xTileDataPosition = { x * _levelManager->_tileMapData->tileWidth, _levelManager->_tileMapData->tileWidth };
				Rectangle TileCollission{ xTileDataPosition.x, yTileDataPosition.x,xTileDataPosition.y,yTileDataPosition.y };
				if (CheckCollisionRecs(PlayerCollisionBottom, TileCollission)) {
					if (y > yPoint && _direction.y > 0 && ((position.y+ _levelManager->_tileMapData->tileHeight/2)-y* _levelManager->_tileMapData->tileHeight) <= _levelManager->_tileMapData->tileHeight/1.7) {
						newDir.y = 0;
						isGrounded = true;
					}
					else
						isGrounded = false;
				}
				else {
					if(!isGrounded)
						isGrounded = false;
				}
		
				if (CheckCollisionRecs(PlayerCollision, TileCollission)) {
					if (tileCollisionData == 2 || isFullWall) {
						isFullWall = true;
						checkMoreAxisX = true;
					}
					else {
						if (_direction.y < 0) {
							checkMoreAxisX = false;
							newDir.x = _direction.x;
							continue;
						}
						checkMoreAxisX = true;
						
					}
				}
				if (checkMoreAxisX) {
					if (_direction.x < 0 && CheckCollisionRecs(PlayerCollisionLeft, TileCollission)) {
						if (tileCollisionData == 1 && _direction.y < 0 && !isFullWall) {
							continue;
						}
						if (x < xPoint) {
							newDir.x = 0;
						}

					}
					if (_direction.x > 0 && CheckCollisionRecs(PlayerCollisionRight, TileCollission)) {
						if (tileCollisionData == 1 && _direction.y < 0 && !isFullWall) {
							continue;
						}
						if (x > xPoint) {
							newDir.x = 0;
						}
					}
				}
			}
			
		}
	}
	_direction = newDir;
}

void Player::Destroy() {

}
void Player::Render() {
	
	if (_direction.x != 0 && _direction.y==0 && isGrounded && !isShooting) {
		xOffset += 0.2f;
		yOffset = 0;
		if (xOffset >= WALK_FRAMES)
			xOffset = 0;
	}
	else if(_direction.x == 0 && _direction.y == 0 && isGrounded && !isShooting) {
		xOffset += 0.07f;
		yOffset = 2;
		if (xOffset >= IDLE_FRAMES)
			xOffset = 0;
	}
	else if (isGrounded && isShooting && _direction.x == 0) {
		xOffset += 0.2f;
		yOffset = 4;
		if (xOffset >= WALK_THROW_FRAMES) {
			xOffset = 0;
			isShooting = false;
		}
	}
	else if (isGrounded && isShooting && _direction.x != 0) {
		xOffset += 0.2f;
		yOffset = 5;
		if (xOffset >= WALK_THROW_FRAMES) {
			xOffset = 0;
			isShooting = false;
		}
	}
	else if (isJumping && !isFalling) {
		xOffset += 0.07f;
		yOffset = 3;
		if (xOffset >= IDLE_FRAMES)
			xOffset = 0;
	}
	else {
		xOffset += 0.07f;
		yOffset = 1;
		if (xOffset >= IDLE_FRAMES)
			xOffset = 0;
	}
	


	int Offset = -_tileMapData->tileWidth * 0.1f;
	//DrawRectangle(position.x - (_tileMapData->tileWidth) + Offset, position.y - (_tileMapData->tileHeight * 2) + Offset, _tileMapData->tileWidth * 2 - Offset * 2, _tileMapData->tileHeight * 2 - Offset * 2, YELLOW); //Inside

	//DrawRectangle(position.x - (_tileMapData->tileWidth)*0.8, position.y, _tileMapData->tileWidth*1.6, _tileMapData->tileHeight * 0.1, RED); //Bottom
	//DrawRectangle(position.x + (_tileMapData->tileWidth), position.y - _tileMapData->tileHeight * 1.5, _tileMapData->tileWidth * 0.1, _tileMapData->tileHeight * 1, RED); //Right
	//DrawRectangle(position.x - (_tileMapData->tileWidth) - _tileMapData->tileWidth * 0.1, position.y - _tileMapData->tileHeight * 1.5, _tileMapData->tileWidth * 0.1, _tileMapData->tileHeight * 1, RED); //Left

	painter.Paint(playerTexture, position, Vector2{ (float)((int)xOffset) ,yOffset }, Vector2{ (float)_tileMapData->tileWidth * 2, (float)(_tileMapData->tileHeight * 2) }, 0);
}


