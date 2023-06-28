#pragma once
#include "Actor.h"
#include "RectangleColliderComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"

class Player : Actor
{
public:
	Player(Game* pGame);

	virtual void Update(float deltaTime) override;

	enum Status {
		IDLE,
		RUNNING,
		JUMPING,
		CLIMBING
	};

private:
	RectangleColliderComponent* _pRectangleColliderComponent;
	InputComponent* _pInputComponent;
	SpriteComponent* _pSpriteComponent;
	float _moveSpeed = 50;
	bool _isJumping;
	float _accelerationRate = 70; // Pixels per second per second
	Vector2 _velocity; // Pixels per second
	Status _playerStatus;
	bool _facingRight;
};

