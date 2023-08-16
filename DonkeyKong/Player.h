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


private:
	RectangleColliderComponent* _pRectangleColliderComponent;
	InputComponent* _pInputComponent;
	SpriteComponent* _pSpriteComponent;
	Vector2 lastPosition;
	float _moveSpeed = 50;
	bool _isJumping;
	float _accelerationRate = 200; // Pixels per second per second
	bool _facingRight;
};

