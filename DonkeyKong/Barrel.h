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
	float _forwardSpeed = -30;
	float _downwardSpeed = 10;

};

