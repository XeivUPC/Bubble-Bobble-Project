#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player(GameManager* gameManager) {
	_gm = gameManager;
	_gm->calls.updateCall.push_back(this);
	_gm->calls.renderCall.push_back(this);
	renderer = TextureRenderer(Vector2{ -16,16 }, Vector2{ (float)_gm->TILE_WIDTH ,(float)_gm->TILE_HEIGHT * 2 });
	position = { (float)_gm->TILE_WIDTH * 3 ,(float)_gm->TILE_HEIGHT * 27 };

}
void Player::Update() {
	switch (state) {
		case Playing:

			if (position.y > (_gm->MAP_HEIGHT - 0.5) *_gm->TILE_HEIGHT)
				position.y = 0;
			GetInput();
			CheckCollisions();
			Move();
			break;
		case ChangingLevel:
			MoveToSpawnPoint();
			break;
		case Dead:
			break;

		default:
			break;
	}
	
}
void Player::GetInput() {

	if (!isJumping) {
		if (IsKeyDown(KEY_D)) {
			_direction.x = _speed;
			if (!isGrounded) {
				_direction.x = _airSpeed / 1.5;
			}

			renderer.FlipX(true);
		}
		else if (IsKeyDown(KEY_A)) {
			_direction.x = -_speed;
			if (!isGrounded) {
				_direction.x = -_airSpeed / 1.5;
			}
			renderer.FlipX(false);
		}
		else {
			_direction.x = 0;
		}
	}
	else {
		if (isJumping) {
			if (IsKeyDown(KEY_D)) {
				_direction.x += _airSpeed / _jumpMovilityDebuff;
				if (_direction.x > _airSpeed * 2)
					_direction.x = _airSpeed * 2;
				renderer.FlipX(true);
			}
			if (IsKeyDown(KEY_A)) {
				_direction.x += -_airSpeed / _jumpMovilityDebuff;
				if (_direction.x <  -_airSpeed * 2)
					_direction.x = -_airSpeed * 2;
				renderer.FlipX(false);
			}
		}
	}

	
	
	if (IsKeyPressed(KEY_SPACE) && isGrounded && !isJumping && !isShooting) {
		isJumping = true;
		isFalling = false;
		_jumpDistance = 0;
		_jumpSpeed = _jumpInitialSpeed;
		PlaySound(jumpSound);
	}

	_direction.y = _gravity; //g
	if (isJumping)
		Jump();


	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isShooting && isGrounded) {
		isShooting = true;
		xOffset = 0;
		PlaySound(shootSound);
		
	}

}
void Player::Move() {

	position.x += _direction.x * _gm->TILE_HEIGHT / 30;;
	position.y += _direction.y * _gm->TILE_HEIGHT / 30;;
}
void Player::Jump() {
	_jumpDistance += abs(_jumpSpeed);
	if (isFalling) {
		_direction.y = -_jumpSpeed;
		_jumpSpeed -= 0.4;
		if (abs(_jumpSpeed) > _jumpMaxSpeed)
			_jumpSpeed = -_jumpMaxSpeed;
		if (_jumpDistance >= _jumpHeight*1.2 || isGrounded) {
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
	Vector2 newPos = position;
	Level level = *_gm->activeLevel;

#pragma region Colliders
	Rectangle PlayerCollisionBottom = { position.x - (_gm->TILE_WIDTH) * 0.8, position.y, _gm->TILE_WIDTH * 1.6, _gm->TILE_HEIGHT * 0.1 };
	Rectangle PlayerCollisionLeft = { position.x - (_gm->TILE_WIDTH) - _gm->TILE_WIDTH * 0.1, position.y - _gm->TILE_HEIGHT * 1.5, _gm->TILE_WIDTH * 0.1 , _gm->TILE_HEIGHT * 1 };
	Rectangle PlayerCollisionRight = { position.x + (_gm->TILE_WIDTH), position.y - _gm->TILE_HEIGHT * 1.5, _gm->TILE_WIDTH * 0.1 , _gm->TILE_HEIGHT * 1 };

	Rectangle PlayerCollisionTop = { position.x - (_gm->TILE_WIDTH) * 0.8, position.y - _gm->TILE_HEIGHT * 2, _gm->TILE_WIDTH * 1.6, _gm->TILE_HEIGHT * 0.1 };
	

	int Offset = - _gm->TILE_WIDTH * 0.1f;
	Rectangle PlayerCollision = { position.x - (_gm->TILE_WIDTH) + Offset ,position.y - (_gm->TILE_HEIGHT * 2) + Offset, _gm->TILE_WIDTH * 2 - Offset * 2, _gm->TILE_HEIGHT * 2 - Offset * 2 };
#pragma endregiond

	float xPoint = (float)floor(position.x) / _gm->TILE_WIDTH;
	float yPoint = (float)floor(position.y - _gm->TILE_HEIGHT / 2) / _gm->TILE_HEIGHT;

	bool isFullWall = false;
	bool checkMoreAxisX = true;
	bool checkMoreAxisY = true;
	isGrounded = false;
	if (yPoint < 1)
		return;
	for (int y = yPoint - 3; y < yPoint + 3; y++)
	{
		Vector2 yTileDataPosition = { (y)*_gm->TILE_HEIGHT ,_gm->TILE_HEIGHT };
		for (int x = xPoint - 3; x < xPoint + 3; x++)
		{

			if (level.IsTile(x, y, level.Collisions)) {
				int tileCollisionData = level.GetTile(x, y, level.Collisions);
				Vector2 xTileDataPosition = { x * _gm->TILE_WIDTH, _gm->TILE_WIDTH };
				Rectangle TileCollission{ xTileDataPosition.x, yTileDataPosition.x,xTileDataPosition.y,yTileDataPosition.y };

				if (CheckCollisionRecs(PlayerCollisionBottom, TileCollission) && checkMoreAxisY) {
					if (y > yPoint && _direction.y > 0 && ((position.y+ _gm->TILE_HEIGHT/2)-y* _gm->TILE_HEIGHT) <= _gm->TILE_HEIGHT/1.6) {
						newDir.y = 0;
						isGrounded = true;
						newPos.y = y * _gm->TILE_HEIGHT;
					}
					else
						isGrounded = false;
				}
				else {
					if(!isGrounded)
						isGrounded = false;
				}

				if (CheckCollisionRecs(PlayerCollision, TileCollission)) {
					if (tileCollisionData == 2 || isFullWall || tileCollisionData == 3) {
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

				if (CheckCollisionRecs(PlayerCollisionTop, TileCollission) && tileCollisionData == 2 || !checkMoreAxisY) {
					checkMoreAxisY = false;
					checkMoreAxisX = false;
					isGrounded = false;
					newDir.y = _direction.y;
				}
				if (checkMoreAxisX || tileCollisionData==3) {
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
	if (isGrounded)
		position.y = newPos.y;
}
void Player::SetStatus(int index) {
	switch (index) {
		case 0:
			renderer.ChangeTileSize(Vector2{ 16,16 });
			renderer.ChangeOrigin(Vector2{ (float)_gm->TILE_WIDTH ,(float)_gm->TILE_HEIGHT * 2 });
			renderer.FlipX(true);
			state = Playing;
			break;
		case 1:
			isGrounded = false;
			isJumping = false;
			isFalling = false;
			isMoving = false;
			isShooting = false;
			bubbleState = 0;
			renderer.ChangeTileSize(Vector2{32,32});
			renderer.ChangeOrigin(Vector2{ (float)_gm->TILE_WIDTH*2 ,(float)_gm->TILE_HEIGHT * 3 });
			renderer.FlipX(true);
			state = ChangingLevel;
			break;
		case 2:
			state = Dead;
			break;
		default:
			break;
	}
}
void Player::TpToSpawnPoint()
{
	position = { (float)_gm->TILE_WIDTH * 3 ,(float)_gm->TILE_HEIGHT * 27 };
}
void Player::MoveToSpawnPoint()
{
	bool arrived = true;
	/// X
	if (position.x > (float)_gm->TILE_WIDTH * 3) {
		position.x -= _speed/1.2f;
		arrived = false;
	}
	else if (position.x < (float)_gm->TILE_WIDTH * 3) {
		position.x += _speed/ 1.2f;
		arrived = false;
	}

	/// Y
	if (position.y> (float)_gm->TILE_HEIGHT * 27) {
		position.y -= _speed/ 1.2f;
		arrived = false;
	}
	else if (position.y< (float)_gm->TILE_HEIGHT * 27) {
		position.y += _speed/ 1.2f;
		arrived = false;
	}

	if (position.y!= (float)_gm->TILE_HEIGHT * 27 && abs(position.y - (float)_gm->TILE_HEIGHT * 27) < 4)
		position.y = (float)_gm->TILE_HEIGHT * 27;

	if (position.x != (float)_gm->TILE_WIDTH * 3 && abs((float)position.x - (float)_gm->TILE_WIDTH * 3) <4)
		position.x = (float)_gm->TILE_WIDTH * 3;
	if (arrived) {
		bubbleState = 3;
	}

	

}
void Player::Render() {
	switch (state) {
		case Playing:
			if (_direction.x != 0 && _direction.y == 0 && isGrounded && !isShooting) {
				xOffset += 0.2f;
				yOffset = 0;
				if (xOffset >= WALK_FRAMES)
					xOffset = 0;
			}
			else if (_direction.x == 0 && _direction.y == 0 && isGrounded && !isShooting) {
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
			
			renderer.Paint(playerTexture, position, Vector2{ (float)((int)xOffset) ,yOffset }, Vector2{ (float)_gm->TILE_WIDTH * 2, (float)(_gm->TILE_HEIGHT * 2) }, 0);
			break;
		case ChangingLevel:
			if (bubbleState == 0) {
				xOffset += 0.1f;
				yOffset = 3;
				if (xOffset >= 2) {
					xOffset = 0;
					bubbleState = 1;
				}

			}
			else if (bubbleState == 1) {
				xOffset += 0.1f;
				yOffset = 4;
				if (xOffset >= 4) {
					xOffset = 0;
					bubbleState = 2;
				}
			}
			else if (bubbleState ==2) {
				xOffset += 0.1f;
				yOffset = 5;
				if (xOffset >= 2) {
					xOffset = 0;
				}
			}
			else {
				xOffset += 0.05f;
				yOffset = 6;
				if (xOffset >= 2) {
					xOffset = 0;
				}
			}
			renderer.Paint(playerTexture, position, Vector2{ (float)((int)xOffset) ,yOffset }, Vector2{ (float)_gm->TILE_WIDTH * 4, (float)(_gm->TILE_HEIGHT * 4) }, 0);
			break;
		case Dead:

			break;
		default:
			break;
	}
	
	
	//int Offset = -_gm->TILE_WIDTH * 0.1f;
	//DrawRectangle(position.x - (_gm->TILE_WIDTH) + Offset, position.y - (_gm->TILE_HEIGHT * 2) + Offset, _gm->TILE_WIDTH * 2 - Offset * 2, _gm->TILE_HEIGHT * 2 - Offset * 2, YELLOW); //Inside

	//DrawRectangle(position.x - (_gm->TILE_WIDTH)*0.8, position.y, _gm->TILE_WIDTH*1.6, _gm->TILE_HEIGHT * 0.1, RED); //Bottom
	//DrawRectangle(position.x + (_gm->TILE_WIDTH), position.y - _gm->TILE_HEIGHT * 1.5, _gm->TILE_WIDTH * 0.1, _gm->TILE_HEIGHT * 1, RED); //Right
	//DrawRectangle(position.x - (_gm->TILE_WIDTH) - _gm->TILE_WIDTH * 0.1, position.y - _gm->TILE_HEIGHT * 1.5, _gm->TILE_WIDTH * 0.1, _gm->TILE_HEIGHT * 1, RED); //Left

	//DrawRectangle(position.x - (_gm->TILE_WIDTH)*0.8, position.y- _gm->TILE_HEIGHT*2, _gm->TILE_WIDTH*1.6, _gm->TILE_HEIGHT * 0.1, RED); //Top1
	
	//DrawRectangle(position.x, position.y, 10, 10, RED);
	//DrawRectangle((float)_gm->TILE_WIDTH * 3, (float)_gm->TILE_HEIGHT * 27, 10, 10, RED);
	
}


