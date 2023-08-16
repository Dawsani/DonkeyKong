#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "RectangleColliderComponent.h"

class Barrel : public Actor
{
public:
	Barrel(Game *pGame);
	virtual void Update(float deltaTime) override;

private:
	SpriteComponent* _pSpriteComponent;
	MoveComponent* _pMoveComponent;
	RectangleColliderComponent* _pRectangleColliderComponent;
	bool _isFalling;
	bool _wasFalling;
	float _direction = 1;
	const float SPEED = 50;
	const float DOWNWARD_SPEED = 100;
};

